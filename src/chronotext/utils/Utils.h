#pragma once

#include "cinder/app/App.h"
#include "cinder/Utilities.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <boost/algorithm/string.hpp>

#if defined(CINDER_MSW)
#include "cinder/msw/OutputDebugStringStream.h"
#elif defined(CINDER_ANDROID)
#include "cinder/android/LogStream.h"
#elif defined(CINDER_MAC) && defined(FORCE_SYSLOG)
#include "chronotext/utils/SyslogStringStream.h"
#endif

#if defined(CINDER_MSW)
static cinder::msw::dostream *CHROUT;
#elif defined(CINDER_ANDROID)
static cinder::android::dostream *CHROUT;
#elif defined(CINDER_MAC) && defined(FORCE_SYSLOG)
static chr::mac::dostream *CHROUT;
#endif

static inline std::ostream& chrout()
{
#if defined(CINDER_MSW)
    if (!CHROUT)
    {
        CHROUT = new cinder::msw::dostream;
    }
    return *CHROUT;
#elif defined(CINDER_ANDROID)
    if (!CHROUT)
    {
        CHROUT = new cinder::android::dostream;
    }
    return *CHROUT;
#elif defined(CINDER_MAC) && defined(FORCE_SYSLOG)
    if (!CHROUT)
    {
        CHROUT = new chr::mac::dostream;
    }
    return *CHROUT;
#else
    return std::cout;
#endif
}

#define LOGI chrout()

#if defined(DEBUG) || defined(FORCE_LOG)
#define LOGD chrout()
#else
#define LOGD false && chrout()
#endif

// ---

/*
 * cout REDIRECTION, AS DESCRIBED IN http://www.cplusplus.com/reference/iostream/ios/rdbuf/
 */

static std::streambuf *gLogBackup = NULL;
static std::ofstream gLogFileStream;

static void logToFile(const ci::fs::path &filePath)
{
    if (!gLogBackup)
    {
        gLogFileStream.open(filePath.string().c_str());
        gLogBackup = chrout().rdbuf();
        
        std::streambuf *psbuf = gLogFileStream.rdbuf();
        chrout().rdbuf(psbuf);
    }
}

static void logToConsole()
{
    if (gLogBackup)
    {
        chrout().rdbuf(gLogBackup);
        gLogFileStream.close();
        gLogBackup = NULL;
    }
}

// ---

static std::string hexDump(const char *data, int size)
{
    std::stringstream s;
    s << std::hex;

    for (int i = 0; i < size; i++)
    {
        s << std::setfill('0') << std::setw(2) << (*data++ & 0xff) << " ";
    }
    
    return s.str();
}

// ---

/*
 * REFERENCE: http://stackoverflow.com/a/10096779/50335
 */

static std::string prettyBytes(uint64_t numBytes, int precision = 2)
{
    const char *abbrevs[] = { "TB", "GB", "MB", "KB" };
    const size_t numAbbrevs = sizeof(abbrevs) / sizeof(abbrevs[0]);

    uint64_t maximum = 0x1L << (10 * (numAbbrevs+1));//pow(1024, numAbbrevs);
    
    for (size_t i = 0; i < numAbbrevs; ++i)
    {
        if (numBytes > maximum)
        {
            std::stringstream s;
            s << std::fixed << std::setprecision(precision) << numBytes / (double)maximum << " " << abbrevs[i];
            return s.str();
        }
        
        maximum /= 1024;
    }
    
    std::stringstream s;
    s << numBytes << " Bytes";
    return s.str();
}

// ---

static int search(float *array, float value, int min, int max)
{
    int mid = (min + max) >> 1;
    
    while (min < mid)
    {
        if (array[mid - 1] < value)
        {
            min = mid;
        }
        else if (array[mid - 1] > value)
        {
            max = mid;
        }
        else
        {
            min = max = mid;
        }
        mid = (min + max) >> 1;
    }
    
    return mid - 1;
}

static inline int search(const std::vector<float> &array, float value, int min, int max)
{
    return search((float*)array.data(), value, min, max);
}

// ---

std::string wstringToUtf8(const std::wstring &s);
std::wstring utf8ToWstring(const std::string &s);
