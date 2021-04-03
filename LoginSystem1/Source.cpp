#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextBox.h"

using namespace sf;

struct scn2
{
	bool email = false;
	bool password = false;
};

struct scn3
{
	bool email = false;
	bool confirmEmail = false;
	bool password = false;
	bool confirmPassword = false;
};

struct account
{
	std::string email;
	std::string password;
};

int scene = 1, i = 1;
scn2 scene2;
scn3 scene3;
account acc[100];
bool first = true;

void input()
{
	std::ifstream fin("login.txt", std::ios::in | std::ios::out);
	while (fin>> acc[i].email)
	{
		fin >> acc[i].password;
		i++;
	}
	fin.close();
}

int main()
{
	RenderWindow window(VideoMode(600, 600), "Login System made by Silvian Achim");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;

	t1.loadFromFile("Login.png");
	t2.loadFromFile("Register.png");
	t3.loadFromFile("Email.png");
	t4.loadFromFile("Password.png");
	t5.loadFromFile("Submit.png");
	t6.loadFromFile("Back.png");
	t7.loadFromFile("ConfirmEmail.png");
	t8.loadFromFile("ConfirmPassword.png");
	t9.loadFromFile("LoginOk.png");

	Sprite login(t1);
	Sprite registerr(t2);
	Sprite Email(t3);
	Sprite Password(t4);
	Sprite Submit(t5);
	Sprite Back(t6);
	Sprite ConfirmEmail(t7);
	Sprite ConfirmPassword(t8);
	Sprite LoginOK(t9);

	Font arial;
	arial.loadFromFile("Arial.ttf");

	Textbox textLoginEmail(30, Color::White, false);
	textLoginEmail.setFont(arial);
	Textbox textLoginPassword(30, Color::White, false);
	textLoginPassword.setFont(arial);
	Textbox textRegisterEmail(30, Color::White, false);
	textRegisterEmail.setFont(arial);
	Textbox textRegisterConfirmEmail(30, Color::White, false);
	textRegisterConfirmEmail.setFont(arial);
	Textbox textRegisterPassword(30, Color::White, false);
	textRegisterPassword.setFont(arial);
	Textbox textRegisterConfirmPassword(30, Color::White, false);
	textRegisterConfirmPassword.setFont(arial);

	input();

	std::ofstream fout("login.txt", std::ios::in | std::ios::out);

	while (window.isOpen())
	{
		if (first == true)
		{
			for (int j = 1; j < i; j++)
			{
				fout << acc[j].email << "\n";
				fout << acc[j].password << "\n";
			}
			first = false;
		}
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					int x = Mouse::getPosition(window).x;
					int y = Mouse::getPosition(window).y;
					if (scene == 1)
					{
						if (x >= 75 && x <= 525 && y >= 87 && y <= 257)
						{
							// LOGIN
							scene = 2;
						}
						if (x >= 75 && x <= 525 && y >= 343 && y <= 513)
						{
							// REGISTER
							scene = 3;
						}
					}
					if (scene == 2)
					{
						// back
						if(x>=233 && x<=368 && y>=530 && y<=580)
						{
							scene = 1;
						}
						if (x >= 50 && x <= 200 && y >= 75 && y <= 125)
						{
							// click on email
							scene2.email = true;
							textLoginEmail.setSelected(true);
						}
						if (x >= 50 && x <= 259 && y >= 235 && y <= 285)
						{
							//click on password
							scene2.password = true;
							textLoginPassword.setSelected(true);
						}
						// submit
						if (x >= 143 && x <= 457 && y >= 405 && y <= 480)
						{
							
							std::string e, p;
							e = textLoginEmail.getText();
							p = textLoginPassword.getText();
							if (e.empty() == false && p.empty() == false)
							{
								for (int j = 1; j <= i; j++)
								{
									if (e == acc[j].email && p == acc[j].password)
									{
										scene = 4;
									}
								}
							}
						}
					}
					if (scene == 3)
					{
						// back
						if (x >= 233 && x <= 368 && y >= 530 && y <= 580)
						{
							scene = 1;
						}
						// email
						if (x >= 15 && x <= 165 && y >= 34 && y <= 84)
						{
							scene3.email = true;
							textRegisterEmail.setSelected(true);
						}
						// confirm email
						if (x >= 15 && x <= 293 && y >= 116 && y <= 166)
						{
							scene3.confirmEmail = true;
							textRegisterConfirmEmail.setSelected(true);
						}
						// password
						if (x >= 15 && x <= 224 && y >= 198 && y <= 248)
						{
							scene3.password = true;
							textRegisterPassword.setSelected(true);
						}
						// confirm password
						if (x >= 15 && x <= 329 && y >= 280 && y <= 330)
						{
							scene3.confirmPassword = true;
							textRegisterConfirmPassword.setSelected(true);
						}
						//submit
						if (x >= 143 && x <= 457 && y >= 405 && y <= 480)
						{
							std::string e, ce, p, cp;
							e = textRegisterEmail.getText();
							ce = textRegisterConfirmEmail.getText();
							p = textRegisterPassword.getText();
							cp = textRegisterConfirmPassword.getText();
							if (e.empty() == false && ce.empty() == false && p.empty() == false && cp.empty() == false)
							{
								if (e == ce  && p==cp)
								{
									fout << e << "\n";
									fout << p << "\n";
								}
							}
						}
					}
				}
			}
			if (e.type == Event::TextEntered)
			{
				if (scene == 2)
				{
					if (scene2.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginEmail.setSelected(false);
							scene2.email = false;
						}
						else
						{
							textLoginEmail.typedOn(e);
						}
					}
					else if (scene2.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginPassword.setSelected(false);
							scene2.password = false;
						}
						else
						{
							textLoginPassword.typedOn(e);
						}
					}
				}
				if (scene == 3)
				{
					if (scene3.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterEmail.setSelected(false);
							scene3.email = false;
						}
						else
						{
							textRegisterEmail.typedOn(e);
						}
					}
					else if (scene3.confirmEmail == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmEmail.setSelected(false);
							scene3.confirmEmail = false;
						}
						else
						{
							textRegisterConfirmEmail.typedOn(e);
						}
					}
					else if (scene3.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterPassword.setSelected(false);
							scene3.password = false;
						}
						else
						{
							textRegisterPassword.typedOn(e);
						}
					}
					else if (scene3.confirmPassword == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmPassword.setSelected(false);
							scene3.confirmPassword = false;
						}
						else
						{
							textRegisterConfirmPassword.typedOn(e);
						}
					}
				}
			}
		}
		window.clear(Color(104, 167, 92));
		if (scene == 1)
		{
			login.setPosition(75, 87);
			window.draw(login);
			registerr.setPosition(75, 343);
			window.draw(registerr);
		}
		if (scene == 2)
		{
			Submit.setPosition(143, 405);
			window.draw(Submit);
			Password.setPosition(50, 235);
			window.draw(Password);
			Email.setPosition(50, 75);
			window.draw(Email);
			Back.setPosition(233, 530);
			window.draw(Back);
			textLoginEmail.setPosition({ 210,76 });
			textLoginEmail.drawTo(window);
			textLoginPassword.setPosition({ 269,237 });
			textLoginPassword.drawTo(window);
		}
		if (scene == 3)
		{
			Submit.setPosition(143, 405);
			window.draw(Submit);
			Back.setPosition(233, 530);
			window.draw(Back);
			Email.setPosition(15, 34);
			window.draw(Email);
			ConfirmEmail.setPosition(15, 116);
			window.draw(ConfirmEmail);
			Password.setPosition(15, 198);
			window.draw(Password);
			ConfirmPassword.setPosition(15, 280);
			window.draw(ConfirmPassword);
			textRegisterEmail.setPosition({ 175, 35 });
			textRegisterEmail.drawTo(window);
			textRegisterConfirmEmail.setPosition({ 303,117 });
			textRegisterConfirmEmail.drawTo(window);
			textRegisterPassword.setPosition({ 234,199 });
			textRegisterPassword.drawTo(window);
			textRegisterConfirmPassword.setPosition({ 339,281 });
			textRegisterConfirmPassword.drawTo(window);
		}
		if (scene == 4)
		{
			LoginOK.setPosition(193, 219);
			window.draw(LoginOK);
		}
		window.display();
	}
	return 0;
}