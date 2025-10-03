/*
 * This file is part of Crystal Dock.
 * Copyright (C) 2022 Viet Dang (dangvd@gmail.com)
 *
 * Crystal Dock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Crystal Dock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Crystal Dock.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "multi_dock_view.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QMessageBox>

#include "display/window_system.h"

#include "add_panel_dialog.h"

namespace crystaldock {

MultiDockView::MultiDockView(MultiDockModel* model)
    : model_(model),
      desktopEnv_(DesktopEnv::getDesktopEnv()) {
  connect(model_, SIGNAL(dockAdded(int)), this, SLOT(onDockAdded(int)));
  loadData();
}

/* static */ bool MultiDockView::checkPlatformSupported(const QApplication& app) {
  if (QGuiApplication::platformName().toLower() != "wayland") {
    QMessageBox::critical(nullptr, "Unsupported Platform",
                          "Crystal Dock 2.x only supports Wayland.\n"
                          "For X11, please use Crystal Dock 1.x");
    return false;
  }

  QNativeInterface::QWaylandApplication* waylandApp =
      app.nativeInterface<QNativeInterface::QWaylandApplication>();
  if (!waylandApp) {
    return false;
  }

  return WindowSystem::init(waylandApp->display());
}

void MultiDockView::show() {
  for (const auto& dock : docks_) {
    dock.second->show();
  }
}

void MultiDockView::exit() {
  for (const auto& dock : docks_) {
    dock.second->close();
  }
}

void MultiDockView::onDockAdded(int dockId) {
  docks_[dockId] = std::make_unique<DockPanel>(this, model_, dockId);
  docks_[dockId]->show();
}

void MultiDockView::loadData() {
  docks_.clear();
  for (int dockId = 1; dockId <= model_->dockCount(); ++dockId) {
    docks_[dockId] = std::make_unique<DockPanel>(this, model_, dockId);
  }

  if (docks_.empty()) {
    AddPanelDialog dialog(nullptr, model_, 0 /* dockId not needed */);
    dialog.setMode(AddPanelDialog::Mode::Welcome);
    dialog.exec();
  }
}

}  // namespace crystaldock
