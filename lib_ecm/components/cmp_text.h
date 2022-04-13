#pragma once

#include <SFML/Graphics/Text.hpp>
#include <../lib_ecm/ecm.h>

//Regular text component (White)
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

//Red text component
class RedTextComponent : public Component {
public:
	RedTextComponent() = delete;
	explicit RedTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~RedTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

//Green text component
class GreenTextComponent : public Component {
public:
	GreenTextComponent() = delete;
	explicit GreenTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~GreenTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

//Blue text component
class BlueTextComponent : public Component {
public:
	BlueTextComponent() = delete;
	explicit BlueTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~BlueTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

//Yellow text component
class YellowTextComponent : public Component {
public:
	YellowTextComponent() = delete;
	explicit YellowTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~YellowTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

//Magenta text component
class MagentaTextComponent : public Component {
public:
	MagentaTextComponent() = delete;
	explicit MagentaTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~MagentaTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

//Cyan text component
class CyanTextComponent : public Component {
public:
	CyanTextComponent() = delete;
	explicit CyanTextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~CyanTextComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};
