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

#include "desktop_env.h"

#include <memory>

#include <QtGlobal>
#include <QProcess>
#include <QStringList>

#include <model/application_menu_config.h>
#include <model/multi_dock_model.h>

namespace crystaldock {

QString DesktopEnv::getDesktopEnvName() {
  QStringList desktops = qEnvironmentVariable("XDG_CURRENT_DESKTOP").split(",", Qt::SkipEmptyParts);
  // The format is usually something like 'KDE' or 'labwc:wlroots'.
  constexpr char kGenericDesktop[] = "generic";
  return desktops.isEmpty() ? kGenericDesktop
                            : desktops.first().mid(0, desktops.first().indexOf(':'));
}

}  // namespace crystaldock
