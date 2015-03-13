#ifndef __VIDEO_SAMPLE_VIEW_H__
#define __VIDEO_SAMPLE_VIEW_H__

#include "cocos2d.h"
#include "ui/UIVideoPlayer.h"

class VideoSampleView : public cocos2d::Node
{

public:

	VideoSampleView();
	~VideoSampleView();

	virtual bool init();

	CREATE_FUNC(VideoSampleView);
private:

};

#endif // __VIDEO_SAMPLE_VIEW_H__