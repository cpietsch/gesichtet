//
//  Tracker.h
//  ofApp
//
//  Created by fairbaken on 22.04.13.
//
//

#ifndef ofApp_Tracker_h
#define ofApp_Tracker_h

template <class F>
class TrackerListener {
public:
    
    virtual void blobOn( F ) = 0;
    virtual void blobMoved( F ) = 0;
    virtual void blobOff( F ) = 0;
    
};


template <class T, class F>
class TrackerFollowerEvent : public Tracker<T> {
protected:
    vector<unsigned int> labels;
    vector<F> followers;
    TrackerListener<F>* listener=NULL;
public:
    void setListener(TrackerListener<F>* _listener){
        listener = _listener;
    }
    void draw(){
        for(int i = 0; i < followers.size(); i++) {
            followers[i].draw();
        }
    }
    vector<unsigned int>& track(const vector<T>& objects) {
        Tracker<T>::track(objects);
        // kill missing, update old
        for(int i = 0; i < labels.size(); i++) {
            unsigned int curLabel = labels[i];
            F& curFollower = followers[i];
            if(!Tracker<T>::existsCurrent(curLabel)) {
                curFollower.kill();
            } else {
                curFollower.update(Tracker<T>::getCurrent(curLabel));
                if (listener!=NULL) {
                    listener->blobMoved(followers[i]);
                }
            }
        }
        // add new
        for(int i = 0; i < Tracker<T>::newLabels.size(); i++) {
            unsigned int curLabel = Tracker<T>::newLabels[i];
            labels.push_back(curLabel);
            followers.push_back(F());
            followers.back().setup(Tracker<T>::getCurrent(curLabel));
            followers.back().setLabel(curLabel);
            if (listener!=NULL) {
                listener->blobOn(followers.back());
            }
        }
        // remove dead
        for(int i = labels.size() - 1; i >= 0; i--) {
            if(followers[i].getDead()) {
                unsigned int curLabel = labels[i];
                if (listener!=NULL) {
                    listener->blobOff(followers[i]);
                }
                followers.erase(followers.begin() + i);
                labels.erase(labels.begin() + i);
            }
        }
        // notivy born
        for(int i = labels.size() - 1; i >= 0; i--) {
            if(followers[i].born && !followers[i].added) {
                unsigned int curLabel = labels[i];
                
                followers[i].added = true;
            }
        }
        return labels;
    }
    vector<F>& getFollowers() {
        return followers;
    }
};

template <class F> class RectTrackerFollowerEvent : public TrackerFollowerEvent<cv::Rect, F> {};


#endif
