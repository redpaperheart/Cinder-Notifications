#pragma once

#include "cinder/timeline.h"
#include "Notification.h"

namespace rph {

    class NotificationManager{
      public:
        static NotificationManager* getInstance();
    
        Notification * add(std::string message, float timeout);
        
        void draw();
        
      protected:
        NotificationManager(){};
        NotificationManager(NotificationManager const&){};
        NotificationManager& operator=(NotificationManager const&){return *m_pInstance;};
        static NotificationManager* m_pInstance;
        
        void deleteNotification( Notification *n );
        
        void updateYPos();
        
        std::list<rph::Notification *> mNotifications;
        
    };
}