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

#ifndef CRYSTALDOCK_DESKTOP_ENV_H_
#define CRYSTALDOCK_DESKTOP_ENV_H_

#include <vector>

#include <QString>

#include <model/application_menu_entry.h>

namespace crystaldock {

// Desktop Environment (including lightweight compositor-only environments) specific data/logic.
// Currently supports Hyprland, KDE, Labwc, LXQt, Niri and Wayfire.
class DesktopEnv {
 protected:
  DesktopEnv() = default;

 public:
  virtual ~DesktopEnv() = default;

  static QString getDesktopEnvName();

  static QString getApplicationMenuIcon() { return "start-here"; }
};

}  // namespace crystaldock

#endif  // CRYSTALDOCK_DESKTOP_ENV_H_
