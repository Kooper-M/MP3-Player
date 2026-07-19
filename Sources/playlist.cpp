#include "playlist.h"
namespace fs = std::filesystem;

Playlist::Playlist(fs::path dir) : dir_(dir) {
    if (!fs::exists(dir_)) {
        std::cout << "Path does not exist" << dir_.string() << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (fs::is_regular_file(entry)) {
            playlist_.emplace_back(entry.path());
        }
    }

    playListSize_ = playlist_.size();
}

const Song* Playlist::next() {
    playListPos_ = (1 + playListPos_) % (playListSize_);
    //player_->setSource(filePathList_.at(playListPos_));
    //player_->play();
    if (playlist_.empty()) {
        return nullptr;
    }
    return &playlist_[playListPos_];
}

const Song* Playlist::prev() {
    if (playListPos_ == 0) {
        playListPos_ = playListSize_ - 1;
    } else {
        --playListPos_;
    }
    if (playlist_.empty()) {
        return nullptr;
    }
    return &playlist_[playListPos_];
}

const Song* Playlist::getSong() const{
    if (playlist_.empty()) {
        return nullptr;
    }
    return &playlist_[playListPos_];
}



void Playlist::autoNext() {
    autoNextFlag = !autoNextFlag;
}

bool Playlist::isAutoNext() const {
    return autoNextFlag;
}

const std::vector<Song>* Playlist::getPlaylist() const {
    return &playlist_;
}


