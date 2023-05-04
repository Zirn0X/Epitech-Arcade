/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Class Sound
*/

#ifndef SOUND_HPP
    #define SOUND_HPP
    #include "IObject.hpp"

namespace arcade {
    class Sound : public arcade::ISound {
        public:
            Sound() {};
            ~Sound() {};
            std::string getSoundPath() const override {
                return this->soundPath;
            };

            float getVolume() const override {
                return this->volume;
            };
            void setSoundPath(std::string path) override {
                this->soundPath = path;
            };

            void setVolume(float volume) override {
                this->volume = volume;
            };
            void pauseSound() override {};
            void playSound() override {};
            void stopSound() override {};
        protected:
        private:
            std::string soundPath = "";
            float volume = 0.0;
    };
}

#endif /* !SOUND_HPP */
