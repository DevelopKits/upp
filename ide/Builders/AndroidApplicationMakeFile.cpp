#include "Android.h"

NAMESPACE_UPP

AndroidApplicationMakeFile::AndroidApplicationMakeFile()
{
	
}

AndroidApplicationMakeFile::~AndroidApplicationMakeFile()
{
	
}

String AndroidApplicationMakeFile::ToString() const
{
	String makeFile;
	
	AppendPlatform(makeFile);
	AppendArchitectures(makeFile);
	AppendCppRuntime(makeFile);
	AppendCppFlags(makeFile);
	AppendCFlags(makeFile);
	
	return makeFile;
}

void AndroidApplicationMakeFile::SetPlatform(const String& platform)
{
	this->platform = platform;
}

void AndroidApplicationMakeFile::SetArchitectures(const Vector<String>& architectures)
{
	this->architectures = clone(architectures);
}

void AndroidApplicationMakeFile::AddArchitecture(const String& architecture)
{
	architectures.Add(architecture);
}

void AndroidApplicationMakeFile::SetCppRuntime(const String& cppRuntime)
{
	this->cppRuntime = cppRuntime;
}

void AndroidApplicationMakeFile::SetCppFlags(const String& cppFlags)
{
	this->cppFlags = cppFlags;
}

void AndroidApplicationMakeFile::SetCFlags(const String& cFlags)
{
	this->cFlags = cFlags;
}

void AndroidApplicationMakeFile::AppendPlatform(String& makeFile) const
{
	AndroidMakeFile::AppendString(makeFile, platform, "APP_PLATFORM");
}

void AndroidApplicationMakeFile::AppendArchitectures(String& makeFile) const
{
	AndroidMakeFile::AppendStringVector(makeFile, architectures, "APP_ABI");
}

void AndroidApplicationMakeFile::AppendCppRuntime(String& makeFile) const
{
	AndroidMakeFile::AppendString(makeFile, cppRuntime, "APP_STL");
}

void AndroidApplicationMakeFile::AppendCppFlags(String& makeFile) const
{
	AndroidMakeFile::AppendString(makeFile, cppFlags, "APP_CPPFLAGS");
}

void AndroidApplicationMakeFile::AppendCFlags(String& makeFile) const
{
	AndroidMakeFile::AppendString(makeFile, cFlags, "APP_CFLAGS");
}

END_UPP_NAMESPACE