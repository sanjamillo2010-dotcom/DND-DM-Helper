# GM Campaign Creation Helper

## Description
This tool is designed to help you create your **D&D 3.5e** campaign or mission.

It can generate:

- **NPCs**, including:
  - Race
  - Class
  - First Name
  - Last Name
  - Sexe
  - Age
  - Size
  - Size Category
  
---
## How to make it in a executable file
### Linux

**1. Install the tools**
```bash
sudo apt install git cmake qt6-base-dev qt6-tools-dev qt6-tools-dev-tools libyaml-cpp-dev libxcb-cursor0
```

**2. Clone the project**
```bash
cd ~/Documents
git https://github.com/sanjamillo2010-dotcom/DND-DM-Helper.git
cd DND_MG_Helper_GUI
```

**3. Open in Qt Creator**
- Open Qt Creator
- File → Open File or Project
- Navigate to your cloned folder and open `CMakeLists.txt`
- Click **Configure**

**4. Build and run**
- Click the hammer to build
- Click the green play button to run

**5. Make a shareable executable**
```bash
# Copy executable to desktop
cp build/Desktop-Debug/DND_MG_Helper_GUI ~/Desktop/
cp -r conf/ ~/Desktop/conf/
chmod +x build/Desktop-Debug/DND_MG_Helper_GUI

# Run it
~/Desktop/DND_MG_Helper_GUI
```

**6. Optional — make a Flatpak for wider sharing**
```bash
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install flathub org.kde.Platform//6.7 org.kde.Sdk//6.7
flatpak-builder --repo=myrepo --force-clean build-flatpak com.sanja.DND_MG_Helper.yaml
flatpak --user remote-add --no-gpg-verify myrepo myrepo
flatpak --user install myrepo com.sanja.DND_MG_Helper
flatpak run com.sanja.DND_MG_Helper
```

### Windows

**1. Install the tools**
- Download and install **Qt** from https://www.qt.io/download-qt-installer (free, select Qt 6.7 + Qt Creator during install)
- Download and install **Git** from https://git-scm.com
- Download and install **CMake** from https://cmake.org

**2. Clone the project**
```cmd
cd C:\Users\YourName\Documents
git clone https://github.com/sanjamillo2010-dotcom/DND-DM-Helper.git
cd DND_MG_Helper_GUI
```

**3. Install yaml-cpp**
The easiest way is via vcpkg:
```cmd
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install yaml-cpp
vcpkg integrate install
cd ..
```

**4. Open the project in Qt Creator**
- Open Qt Creator
- File → Open File or Project
- Navigate to your cloned folder and open `CMakeLists.txt`
- Qt Creator will ask you to configure the project — click **Configure**

**5. Tell CMake where vcpkg is**
In Qt Creator go to **Projects → Build → CMake Configuration** and add:
```
CMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

**6. Build and run**
- Click the hammer to build
- Click the green play button to run

**7. Make a shareable executable**
Open the Qt command prompt (search "Qt 6.7 MinGW" in Start menu) and run:
```cmd
cd C:\Users\YourName\Documents\DND_MG_Helper_GUI\build\Desktop-Debug\DND_MG_Helper_GUI
windeployqt DND_MG_Helper_GUI.exe
```
Then copy the entire `Release` folder including your `conf/` folder to share it.

## Configuration

The configuration files are located in the `/conf` directory.

### `NPC_conf.yaml`

You can customize the NPC generator by editing this file:

- You can **add or remove races**, and the tool will use (or stop using) the races you modify.  
  *(Make sure to configure them correctly.)*

- You can **add or remove classes**, and the tool will use (or stop using) the classes you modify.  
  *(Make sure to configure them correctly.)*

- You can **add or remove entries in `usualNames`**, and the tool will use (or stop using) the names you modify.

- You can **add or remove entries in `usualLastNames`**, and the tool will use (or stop using) the last names you modify.
