idf_component_register(SRCS

"Api/DeviceInfoGetHodiHandler.cpp" "Api/DisplayImageSetHandler.cpp" "Api/DisplaySubtitleSetHandler.cpp"

"Devices/DeviceInstanceShelly.cpp" 
"Devices/DeviceInstanceShellyPro3EM.cpp" 
"Devices/DeviceInstanceShellyProEM.cpp" 
"Devices/DeviceInstanceShelly3EM.cpp" 
"Devices/DeviceInstanceShellyEMGen1.cpp" 
"Devices/DeviceInstanceShellyEMGen3.cpp" 
"Devices/DeviceInstanceShellyHT.cpp" 
"Devices/DeviceInstanceShellyPlugS.cpp" 
"Devices/DeviceInstanceTibberPrice.cpp"

"Logic/Display.cpp" "Logic/DisplayLogic.cpp"  "Logic/Segment7.cpp" "Logic/Segment7Large.cpp" 
"Logic/SubtitleDisplayTextBase.cpp" "Logic/SubtitleDisplayTextEnergy.cpp" "Logic/SubtitleDisplayTextClimate.cpp" "Logic/SubtitleDisplayTextStatus.cpp" 
"Logic/SubtitleDisplayTextRssi.cpp" "Logic/SubtitleDisplayTextEnergyPrice.cpp"

"System/ConfigStoreApp.cpp"

"Tasks/DeviceTask.cpp" "Tasks/DisplayTask.cpp"

"main.cpp" "Eelyapp.cpp"

EMBED_TXTFILES ../../eely-hodi-web/index.min.html

REQUIRES esp_http_server esp_http_client esp-tls json nvs_flash spiffs app_update eely-base-esp eely-smart-matrix 
INCLUDE_DIRS "." "Api" "Devices" "Logic" "System" "Tasks" )
