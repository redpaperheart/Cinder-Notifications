#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/timeline.h"
#include "Notification.h"

namespace rph {

    class NotificationManager{
      public:
        static NotificationManager* getInstance();
    
        Notification * add(std::string message, float timeout, ci::ColorA bgColor = ci::ColorA(1.0f,1.0f,1.0f,1.0f), ci::ColorA fontColor = ci::ColorA(0.0f,0.0f,0.0f,1.0f) );
        
        void draw();
        
        void setWindowSize(ci::ivec2 size){ mWindowSize = size;}
        
      protected:
        NotificationManager(){};
        NotificationManager(NotificationManager const&){};
        NotificationManager& operator=(NotificationManager const&){return *m_pInstance;};
        static NotificationManager* m_pInstance;
        
        void deleteNotification( Notification *n );
        
        void updateYPos();
        ci::ivec2 mWindowSize;
        
        std::list<rph::Notification *> mNotifications;
        
    };
}