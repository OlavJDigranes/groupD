#pragma once

#include <SFML/Graphics/Text.hpp>
#include <../lib_ecm/ecm.h>

//Regular text component
class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(double dt) override;

  void render() override;

  ~TextComponent() override = default;

  void SetText(const std::string& str);

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
};

//ESC text component
class ESCTextComponent : public Component {
public:
	ESCTextComponent() = delete;
	explicit ESCTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~ESCTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _ESCfont;
	std::string _ESCstring;
	sf::Text _ESCtext;
};