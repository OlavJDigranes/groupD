#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

//General text component
void TextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition()); 
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  //_font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  //_font = Resources::get<sf::Font>("RobotoMono-Bold.ttf");
  _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
  //_font = Resources::get<sf::Font>("arial.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

//ESC text component
void ESCTextComponent::update(double dt) {
    _ESCtext.setPosition(_parent->getPosition());
}

void ESCTextComponent::render() {
    Renderer::queue(&_ESCtext);
}

ESCTextComponent::ESCTextComponent(Entity* const p, const std::string& str) : Component(p), _ESCstring(str) {
    _ESCtext.setString(_ESCstring);
    _ESCfont = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _ESCtext.setFont(*_ESCfont);
    _ESCtext.setCharacterSize(20); 
}

void ESCTextComponent::SetText(const std::string& str) {
    _ESCstring = str; 
    _ESCtext.setString(_ESCstring);
}