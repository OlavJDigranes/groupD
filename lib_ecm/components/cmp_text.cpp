#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

using namespace sf; 

//General text component
void TextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition()); 
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

void TextComponent::ChangeColor(const sf::Color color)
{
    _text.setFillColor(color);
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

//Red Text Component
void RedTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void RedTextComponent::render() { Renderer::queue(&_text); }

RedTextComponent::RedTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color::Red);
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold);
}

void RedTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Green Text Component
void GreenTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void GreenTextComponent::render() { Renderer::queue(&_text); }

GreenTextComponent::GreenTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color::Green);
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold);
}

void GreenTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Blue Text Component
void BlueTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void BlueTextComponent::render() { Renderer::queue(&_text); }

BlueTextComponent::BlueTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color{2,133,169,255});
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold);
}

void BlueTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Yellow Text Component
void YellowTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void YellowTextComponent::render() { Renderer::queue(&_text); }

YellowTextComponent::YellowTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color::Yellow);
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold);
}

void YellowTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Magenta Text Component
void MagentaTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void MagentaTextComponent::render() { Renderer::queue(&_text); }

MagentaTextComponent::MagentaTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color::Magenta);
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold);
}

void MagentaTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Cyan Text Component
void CyanTextComponent::update(double dt)
{
    _text.setPosition(_parent->getPosition());
}

void CyanTextComponent::render() { Renderer::queue(&_text); }

CyanTextComponent::CyanTextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _text.setFillColor(Color::Cyan);
    _text.setOutlineColor(Color::White);
    _font = Resources::get<sf::Font>("ShadowsIntoLight-Regular.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(40);
    _text.setStyle(Text::Bold); 
}

void CyanTextComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

//Commented lines:
  //_font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  //_font = Resources::get<sf::Font>("RobotoMono-Bold.ttf");
  //_font = Resources::get<sf::Font>("arial.ttf");
