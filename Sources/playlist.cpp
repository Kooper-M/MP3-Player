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

Song Playlist::next() {
    playListPos_ = (1 + playListPos_) % (playListSize_);
    //player_->setSource(filePathList_.at(playListPos_));
    //player_->play();
    return playlist_[playListPos_];
}

Song Playlist::prev() {
    if (playListPos_ == 0) {
        playListPos_ = playListSize_ - 1;
    } else {
        --playListPos_;
    }
    return playlist_[playListPos_];
}

Song Playlist::getSong() const{
    return playlist_[playListPos_];
}


