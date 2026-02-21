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
  - Level
  - XP
  - HP
  - Alignment
  - Deity
  - Caracteristique (Not fully devloped)
  
---
## How to run

In the terminal
`cd Documents/workspace/GM_Helper/  
rm -rf build  
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug  
cmake --build build --parallel -- VERBOSE=1 2>&1  
./build/GM_Helper`  

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

- You can **add or remove deities**, and the tool will use (or stop using) the deities you modify.
