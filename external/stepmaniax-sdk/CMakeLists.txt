set(SMXSDK_SOURCES
	"sdk/Windows/Helpers.cpp"
	"sdk/Windows/Helpers.h"
	"sdk/Windows/SMX.cpp"
	"sdk/Windows/SMXBuildVersion.h"
	"sdk/Windows/SMXConfigPacket.cpp"
	"sdk/Windows/SMXConfigPacket.h"
	"sdk/Windows/SMXDevice.cpp"
	"sdk/Windows/SMXDevice.h"
	"sdk/Windows/SMXDeviceConnection.cpp"
	"sdk/Windows/SMXDeviceConnection.h"
	"sdk/Windows/SMXDeviceSearch.cpp"
	"sdk/Windows/SMXDeviceSearch.h"
	"sdk/Windows/SMXDeviceSearchThreaded.cpp"
	"sdk/Windows/SMXDeviceSearchThreaded.h"
	"sdk/Windows/SMXGif.cpp"
	"sdk/Windows/SMXGif.h"
	"sdk/Windows/SMXHelperThread.cpp"
	"sdk/Windows/SMXHelperThread.h"
	"sdk/Windows/SMXManager.cpp"
	"sdk/Windows/SMXManager.h"
	"sdk/Windows/SMXPanelAnimation.cpp"
	"sdk/Windows/SMXPanelAnimation.h"
	"sdk/Windows/SMXPanelAnimationUpload.cpp"
	"sdk/Windows/SMXPanelAnimationUpload.h"
	"sdk/Windows/SMXThread.cpp"
	"sdk/Windows/SMXThread.h"
)

add_library(smx STATIC ${SMXSDK_SOURCES})

target_link_libraries(smx PUBLIC hid)
target_include_directories(smx INTERFACE "sdk")