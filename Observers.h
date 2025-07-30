//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_OBSERVERS_H
#define ADVACEDPROGRAMINGZIT2_OBSERVERS_H

#include <vector>
#include <memory>
#include <list>
#include "BGTile.h"

class World;
class Score;
class Camera;

// Observer interfaces
class WorldObserver {
public:
    virtual void update(std::weak_ptr<World> world) = 0;
    virtual ~WorldObserver() = default;
};

class ScoreObserver {
public:
    virtual void update(std::weak_ptr<Score> score) = 0;
    virtual ~ScoreObserver() = default;
};

class CameraObserver {
public:
    virtual void update(std::weak_ptr<Camera> camera) = 0;
    virtual ~CameraObserver() = default;
};

// Score class
class Score : public WorldObserver, public std::enable_shared_from_this<Score> {
private:
    int minusPoints;
    std::list<std::weak_ptr<ScoreObserver>> _observers;
    int maxScore;
    int currentScore;
    float height;

    void updateObservers();
public:
    Score();
    void update(std::weak_ptr<World> world) override;
    void addObserver(const std::shared_ptr<ScoreObserver>& observer);
    int getCurrentScore() const;
    int getMaxScore() const;
};

using tileDescription = std::pair<std::pair<float, float>, std::pair<Color, BonusType>>;
// Camera class
class Camera : public WorldObserver, public std::enable_shared_from_this<Camera> {
private:
    std::list<std::weak_ptr<CameraObserver>> _observers;
    std::vector<tileDescription> _tileDescription;
    std::pair<float, float> playerCoordinates;
    float height;
    bool gameOver;
    void normalizedCoordinates(const float worldHeight);
    void updateObservers();
public:
    Camera();

    const std::vector<tileDescription> &getTileDescription() const;

    bool isGameOver() const;

    const std::pair<float, float> &getPlayerCoordinates() const;

    void update(std::weak_ptr<World> world) override;
    void addObserver(const std::shared_ptr<CameraObserver>& observer);
};

/*class WorldObserver {
public:
    virtual void update(std::weak_ptr<World> world) = 0;
    virtual ~WorldObserver() = default;
};

class Score;
class ScoreObserver {
    virtual void update(std::weak_ptr<Score> score) = 0;
    virtual ~ScoreObserver() = default;
};
class Camera;
class CameraObserver {
    virtual void update(std::weak_ptr<Camera> camera) = 0;
    virtual ~CameraObserver() = default;
};

class Score : public WorldObserver {
private:
    std::list<std::shared_ptr<ScoreObserver>> _observers;
    int maxScore;
    int currentScore;
    float height;
    void updateObservers() const;
public:
    void update(std::weak_ptr<World> world) override;
    Score();
    void addObserver(const std::shared_ptr<ScoreObserver>& observer);
};

class Camera : public WorldObserver {
private:
    std::list<std::shared_ptr<CameraObserver>> _observers;
    std::vector<std::pair<float, float>> tileCoordinates;
    std::pair<float, float> playerCoordinates;
    float height;
    void normalizedCoordinates();
    void updateObservers() const;
public:
    void update(std::weak_ptr<World> world) override;
    Camera();
    void addObserver(const std::shared_ptr<CameraObserver>& observer);
};*/




/*template <typename T>
class Observer {
public:
    virtual void update(std::shared_ptr<T> subject) = 0;
    virtual ~Observer() = default;
};

template <typename T>
class Subject {
private:
    std::vector<std::weak_ptr<Observer<T>>> observers;

public:
    void addObserver(const std::shared_ptr<Observer<T>>& obs) {
        observers.push_back(obs);
    }

    void removeObserver(const std::shared_ptr<Observer<T>>& obs) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            auto shared = it->lock();
            if (!shared || shared == obs) {
                it = observers.erase(it);  // Verwijder en behoud geldige iterator
            } else {
                ++it;
            }
        }
    }

protected:
    void notifyObservers(std::shared_ptr<T> self) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto obs = it->lock()) {
                obs->update(self);
                ++it;
            } else {
                // Observer is expired → verwijderen
                it = observers.erase(it);
            }
        }
    }
};

class Score : public Observer<World>, public Subject<Score>, public std::enable_shared_from_this<Score> {
private:
    int maxScore = 0;
    int currentScore = 0;
    float height = 0.0f;

public:
    Score();
    void update(std::shared_ptr<World> world) override;

    int getCurrentScore() const { return currentScore; }
    int getMaxScore() const { return maxScore; }
};


class Camera : public Observer<World>, public Subject<Camera>, public std::enable_shared_from_this<Camera> {
private:
    std::vector<std::pair<float, float>> tileCoordinates;
    std::pair<float, float> playerCoordinates{0, 0};
    float height = 0;

    void normalizedCoordinates();

public:
    Camera() = default;
    void update(std::shared_ptr<World> world) override;
    std::pair<float, float> getPlayerPos() const { return playerCoordinates; }
    const std::vector<std::pair<float, float>>& getTileCoordinates() const { return tileCoordinates; }
};*/

#endif //ADVACEDPROGRAMINGZIT2_OBSERVERS_H
