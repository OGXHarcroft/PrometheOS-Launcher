#include "systemInfoScene.h"
#include "sceneManager.h"

#include "..\context.h"
#include "..\drawing.h"
#include "..\component.h"
#include "..\ssfn.h"
#include "..\inputManager.h"
#include "..\stringUtility.h"
#include "..\xboxConfig.h"
#include "..\theme.h"

systemInfoScene::systemInfoScene(systemInfoCategoryEnum systemInfoCategory)
{
	mSelectedControl = 0;
	mInfoItems = new pointerVector<char*>(false);
	mSystemInfoCategory = systemInfoCategory;
	
	if (mSystemInfoCategory == systemInfoCategoryConsole)
	{
		char* cpuSpeed = stringUtility::formatString("CPU: %4.2fMHz", xboxConfig::getCPUFreq());
		mInfoItems->add(cpuSpeed);

		char* xboxVersionString = xboxConfig::getXboxVersionString();
		char* xboxVersion = stringUtility::formatString("Xbox Rev: %s", xboxVersionString);
		mInfoItems->add(xboxVersion);
		free(xboxVersionString);

		char* totalMemory = stringUtility::formatString("RAM: %uMB", utils::getTotalPhysicalMemory() >> 20);
		mInfoItems->add(totalMemory);

		char* serialString = xboxConfig::getSerialString();
		char* serial = stringUtility::formatString("Serial: %s", serialString);
		mInfoItems->add(serial);
		free(serialString);

		char* macString = xboxConfig::getMacString();
 		char* mac = stringUtility::formatString("Mac: %s", macString);
		mInfoItems->add(mac);
		free(macString);
	}
	else if (mSystemInfoCategory == systemInfoCategoryStorage)
	{
		const char* model = HalDiskModelNumber->Buffer ? HalDiskModelNumber->Buffer : "";
		char* diskModelNumberString = stringUtility::trim(model, ' ');
		char* diskModelNumber = stringUtility::formatString("HDD Model: %s", diskModelNumberString);
		mInfoItems->add(diskModelNumber);
		free(diskModelNumberString);

		const char* serial = HalDiskSerialNumber->Buffer ? HalDiskSerialNumber->Buffer : "";
		char* diskSerialNumberString = stringUtility::trim(serial, ' ');
		char* diskSerialNumber = stringUtility::formatString("HDD Serial: %s", diskSerialNumberString);
		mInfoItems->add(diskSerialNumber);
		free(diskSerialNumberString);

				// hdd model dvd model
	}
	else if (mSystemInfoCategory == systemInfoCategoryAudio)
	{
		char* audioModeString = xboxConfig::getAudioModeString();
		char* audioMode = stringUtility::formatString("Audio Mode: %s", audioModeString);
		mInfoItems->add(audioMode);
		free(audioModeString);

		char* ac3 = stringUtility::formatString("Dolby digital (AC3): %s", xboxConfig::getAudioAC3() ? "Enabled" : "Disabled");
		mInfoItems->add(ac3);

		char* dts = stringUtility::formatString("DTS: %s", xboxConfig::getAudioDTS() ? "Enabled" : "Disabled");
		mInfoItems->add(dts);
	}
	else if (mSystemInfoCategory == systemInfoCategoryVideo)
	{
		char* videoStandardString = xboxConfig::getVideoStandardString();
		char* videoStandard = stringUtility::formatString("Video Standard: %s", videoStandardString);
		mInfoItems->add(videoStandard);
		free(videoStandardString);

		char* gameRegionString = xboxConfig::getGameRegionString();
		char* gameRegion = stringUtility::formatString("Game Region: %s", gameRegionString);
		mInfoItems->add(gameRegion);
		free(gameRegionString);

		char* dvdRegionString = xboxConfig::getDvdRegionString();
		char* dvdRegion = stringUtility::formatString("DVD Region: %s", dvdRegionString);
		mInfoItems->add(dvdRegion);
		free(dvdRegionString);

		char* avPackString = xboxConfig::getAvPackString();
		char* avPack = stringUtility::formatString("AV Pack: %s", avPackString);
		free(avPackString);

		char* encoderString = xboxConfig::getEncoderString();
		char* encoder = stringUtility::formatString("Encoder: %s", encoderString);
		mInfoItems->add(encoder);
		free(encoderString);
	}
	else if (mSystemInfoCategory == systemInfoCategoryAbout)
	{
		char *app = strdup("PrometheOS Launcher");
		mInfoItems->add(app);

		char *by = strdup("Team Resurgent");
		mInfoItems->add(by);

		char *coded = strdup("Coded By: EqUiNoX");
		mInfoItems->add(coded);
	}
}

systemInfoScene::~systemInfoScene()
{
	delete(mInfoItems);
}

void systemInfoScene::update()
{
	// Exit Action

	if (inputManager::buttonPressed(ButtonB))
	{
		sceneManager::popScene();
		return;
	}
	
	// Down Actions

	if (inputManager::buttonPressed(ButtonDpadDown))
	{
		if (mInfoItems != NULL)
		{
			mSelectedControl = mSelectedControl < (int)(mInfoItems->count() - 1) ? mSelectedControl + 1 : 0;
		}
	}

	// Up Actions

	if (inputManager::buttonPressed(ButtonDpadUp))
	{
		if (mInfoItems != NULL)
		{
			mSelectedControl = mSelectedControl > 0 ? mSelectedControl - 1 : (int)(mInfoItems->count() - 1); 
		}
	}
}

void systemInfoScene::render()
{
	component::panel(theme::getPanelFillColor(), theme::getPanelStrokeColor(), 16, 16, 688, 448);

	for (int i = 0; i < 3; i++)
	{
		if (mSystemInfoCategory == systemInfoCategoryConsole)
		{
			drawing::drawBitmapStringAligned(context::getBitmapFontMedium(), "System Info: Console", i == 2 ? theme::getHeaderTextColor() : 0xff000000, theme::getHeaderAlign(), 40, theme::getHeaderY(), 640);
		}
		else if (mSystemInfoCategory == systemInfoCategoryStorage)
		{
			drawing::drawBitmapStringAligned(context::getBitmapFontMedium(), "System Info: Storage", i == 2 ? theme::getHeaderTextColor() : 0xff000000, theme::getHeaderAlign(), 40, theme::getHeaderY(), 640);
		}
		else if (mSystemInfoCategory == systemInfoCategoryAudio)
		{
			drawing::drawBitmapStringAligned(context::getBitmapFontMedium(), "System Info: Audio", i == 2 ? theme::getHeaderTextColor() : 0xff000000, theme::getHeaderAlign(), 40, theme::getHeaderY(), 640);
		}
		else if (mSystemInfoCategory == systemInfoCategoryVideo)
		{
			drawing::drawBitmapStringAligned(context::getBitmapFontMedium(), "System Info: Video", i == 2 ? theme::getHeaderTextColor() : 0xff000000, theme::getHeaderAlign(), 40, theme::getHeaderY(), 640);
		}
		else if (mSystemInfoCategory == systemInfoCategoryAbout)
		{
			drawing::drawBitmapStringAligned(context::getBitmapFontMedium(), "System Info: About", i == 2 ? theme::getHeaderTextColor() : 0xff000000, theme::getHeaderAlign(), 40, theme::getHeaderY(), 640);
		}
	}

	uint32_t yPos = 96;

	int32_t maxItems = 7;

	int32_t start = 0;
	if ((int32_t)mInfoItems->count() >= maxItems)
	{
		start = min(max(mSelectedControl - (maxItems / 2), 0), (int32_t)mInfoItems->count() - maxItems);
	}

	int32_t itemCount = min(start + maxItems, (int32_t)mInfoItems->count()) - start; 
	if (itemCount > 0)
	{
		uint32_t yPos = (context::getBufferHeight() - ((itemCount * 40) - 10)) / 2;
		yPos += theme::getCenterOffset();

		for (int32_t i = 0; i < itemCount; i++)
		{
			uint32_t index = start + i;
			if (index >= mInfoItems->count())
			{
				continue;
			}
			char* infoItem = mInfoItems->get(index);
			component::textBox(infoItem, mSelectedControl == index, false, horizAlignmentCenter, 40, yPos, 640, 30);
			yPos += 40;
		}
	}
	else
	{
		int yPos = ((context::getBufferHeight() - 44) / 2);
		yPos += theme::getCenterOffset();

		component::textBox("No items", false, false, horizAlignmentCenter, 193, 225, 322, 44);
	}
	drawing::drawBitmapStringAligned(context::getBitmapFontSmall(), "\xC2\xA2 Back", theme::getFooterTextColor(), horizAlignmentRight, 40, theme::getFooterY(), 640);
}
