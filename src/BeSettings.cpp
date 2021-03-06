#include "BeSettings.h"
#include "BeUtils.h"

#include <File.h>
#include <Errors.h>
#include <StorageDefs.h>

BeSettings::BeSettings(const char *fileName)
            : BMessage()
{
	pathToSettingsFile = BeUtils::GetPathToSettingsFile(fileName);
}

void
BeSettings::SetSettingsString(const char *name, const char *string)
{
	BString buffer;
	if(FindString(name, &buffer) != B_OK)
	{
		AddString(name, string);
	}
	else
	{
		ReplaceString(name, string);
	}
}

bool
BeSettings::DumpSettingsToFile(void)
{
	BFile out;
	if(out.SetTo(pathToSettingsFile.String(), B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE) != B_OK)
	{
		return false;
	}
	if(Flatten(&out) != B_OK)
	{
		return false;
	}
	out.Unset();

	return true;
}

bool
BeSettings::ReadSettingsFromFile(void)
{
	BFile in;
	if(in.SetTo(pathToSettingsFile.String(), B_READ_ONLY) != B_OK)
	{
		return false;
	}
	if(Unflatten(&in) != B_OK)
	{
		return false;
	}

	return true;
}

const char *
BeSettings::GetSettingsString(const char *name) const
{
	BString buffer;
	if (FindString(name, &buffer) != B_OK)
	{
		return "";
	}

	return buffer.String();
}

BeSettings::~BeSettings(void)
{

}
