#pragma once

#include "cinder/DataSource.h"

#if defined(CHR_COMPLEX) && defined(CINDER_ANDROID)
#include <android/asset_manager.h>

static AAssetManager *gAssetManager;
static ci::fs::path gInternalDataPath;
static ci::fs::path gApkPath;
#endif

typedef std::shared_ptr<class InputSource> InputSourceRef;

class InputSource
{
    int type;
    
    std::string resourceName;
    int mswID;
    std::string mswType;
    ci::fs::path filePath;
    std::string filePathHint;
    
    InputSource(int type) : type(type) {}

public:
    enum
    {
        TYPE_RESOURCE,
        TYPE_RESOURCE_MSW,
        TYPE_FILE
    };
    
    /*
     * FOR "DYNAMIC" RESOURCES:
     *
     * OSX, IOS: isFile() WILL RETURN true
     * ANDROID: isFile() WILL RETURN false
     */
    static InputSourceRef getResource(const std::string &resourceName);
    static ci::DataSourceRef loadResource(const std::string &resourceName);
    
    /*
     * FOR "STATIC" RESOURCES EMBEDDED INSIDE THE EXECUTABLE ON MSW:
     * isFile() WILL RETURN false
     */
    static InputSourceRef getResource(const std::string &resourceName, int mswID, const std::string &mswType);
    static ci::DataSourceRef loadResource(const std::string &resourceName, int mswID, const std::string &mswType);
    
    static InputSourceRef getFileInDocuments(const std::string &relativePath);
    static ci::DataSourceRef loadFileInDocuments(const std::string &relativePath);
    
    static InputSourceRef getFile(const ci::fs::path &filePath);
    ci::DataSourceRef loadFile(const ci::fs::path &filePath);
    
    ci::DataSourceRef loadDataSource();
    
    bool isFile() const;
    ci::fs::path getFilePath() const;
    
    std::string getFilePathHint() const;
    std::string getUniqueName() const;
    
    void setFilePathHint(const std::string &hint);

#if defined(CINDER_COCOA)
    static ci::fs::path getResourcePath();
    static ci::fs::path getResourcePath(const std::string &resourceName);
#endif

#if defined(CHR_COMPLEX) && defined(CINDER_ANDROID)
    static void setAndroidAssetManager(AAssetManager *assetManager);
    static AAssetManager* getAndroidAssetManager();
    
    static void setAndroidInternalDataPath(const std::string &internalDataPath);
    static ci::fs::path getAndroidInternalDataPath();
    
    static void setAndroidApkPath(const std::string &apkPath);
    static ci::fs::path getAndroidApkPath();
#endif
};
