# GM Campaign Creation Helper

## Description
This tool is designed to help you create your **D&D 3.5e** campaign or mission. 
The tool has a GUI and a Comand line mode. Note that if you want to youse the comand line mode you need to launch it from the Terminal or cmd.
For linux and Windows 
```bash
./DND_MG_Helper_GUI-v'vertion'-'yourOS'
```

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
  - Level
  - XP
  
---
## How to make it in a executable file
You can skip this part if there is already a working executable file in the repository. They will be in /Executable/yourOS
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
The /conf folder will be there too. Bundle theme in a single folder for easy configuration. Correct the spelling.

**6. Optional — make a Flatpak for wider sharing**
```bash
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install flathub org.kde.Platform//6.7 org.kde.Sdk//6.7
flatpak-builder --repo=myrepo --force-clean build-flatpak com.sanja.DND_MG_Helper.yaml
flatpak --user remote-add --no-gpg-verify myrepo myrepo
flatpak --user install myrepo com.sanja.DND_MG_Helper
flatpak run com.sanja.DND_MG_Helper
```
---
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
