#include "resource_path.h"

#include <filesystem>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

std::string RESOURCES_PATH;

void initialize_resource_path()
{
#ifdef __APPLE__

    CFBundleRef bundle = CFBundleGetMainBundle();

    CFURLRef resourcesURL =
            CFBundleCopyResourcesDirectoryURL(bundle);

    char path[4096];

    CFURLGetFileSystemRepresentation(
            resourcesURL,
            true,
            reinterpret_cast<UInt8*>(path),
            sizeof(path)
    );

    CFRelease(resourcesURL);

    RESOURCES_PATH = path;

#else

#ifdef PRODUCTION_BUILD
    RESOURCES_PATH =
            (std::filesystem::current_path() / "Assets").string();
#else
    RESOURCES_PATH = DEVELOPMENT_RESOURCES_PATH;
#endif

#endif
}