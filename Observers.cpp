//
// Created by ruben on 23/07/25.
//

#include "Observers.h"
#include <cmath>
#include <iostream>
#include "World.h"



Score::Score() : height{0}, maxScore{0}, currentScore{0}, _observers{}, minusPoints{0} {}

void Score::update(std::weak_ptr<World> world) {
    if (auto worldShared = world.lock()) {
        currentScore = worldShared->getMaxPlayerHeight()-50;
        if (currentScore-minusPoints>maxScore) {
            maxScore = currentScore-minusPoints;
        }
        if (worldShared->isLastJumpedOn()) {
            minusPoints += 250;
        }
        updateObservers();
    }
}

void Score::addObserver(const std::shared_ptr<ScoreObserver>& observer) {
    _observers.push_back(observer);
}

void Score::updateObservers() {
    for (auto it = _observers.begin(); it != _observers.end(); ) {
        if (auto obs = it->lock()) {
            obs->update(shared_from_this());
            ++it;
        } else {
            it = _observers.erase(it); // verwijder dode observer
        }
    }
}

int Score::getCurrentScore() const {
    return currentScore-minusPoints;
}

int Score::getMaxScore() const {
    return maxScore;
}

Camera::Camera() : _tileDescription{}, playerCoordinates{0.0f, 0.0f}, height{0.0f}, _observers{}, gameOver(false) {}

void Camera::update(std::weak_ptr<World> world) {
    if (auto worldShared = world.lock()) {
        _tileDescription.clear();
        playerCoordinates = worldShared->getPlayerPos();
        height = worldShared->getWorldOffSetY();
        for (const auto& tile : worldShared->getTiles()) {
            _tileDescription.push_back({{tile->getPosX(), tile->getPosY()},{tile->getColor(), tile->getBonusType()}});
        }
        normalizedCoordinates(worldShared->getMaxHeight());
        updateObservers();
    }
}

void Camera::normalizedCoordinates(const float worldHeight) {
    for (auto& tile : _tileDescription) {
        tile.first.second -= height;
        tile.first.second = worldHeight - tile.first.second;
    }
    playerCoordinates.second -= height;
    playerCoordinates.second = worldHeight - playerCoordinates.second;
    if (playerCoordinates.second > 700) {
        gameOver = true;
    }
}

void Camera::addObserver(const std::shared_ptr<CameraObserver>& observer) {
    _observers.push_back(observer);
}

void Camera::updateObservers() {
    if (_observers.empty()) {
    }
    for (auto it = _observers.begin(); it != _observers.end(); ) {
        if (auto obs = it->lock()) {
            obs->update(shared_from_this());
            ++it;
        } else {
            it = _observers.erase(it);
        }
    }
}

const std::vector<tileDescription> &Camera::getTileDescription() const {
    return _tileDescription;
}

const std::pair<float, float> &Camera::getPlayerCoordinates() const {
    return playerCoordinates;
}

bool Camera::isGameOver() const {
    return gameOver;
}
