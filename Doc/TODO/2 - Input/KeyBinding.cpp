#include "KeyBinding.hpp"
#include <iostream>

namespace lp
{

std::string keyToString(sf::Keyboard::Key const& key)
{
    switch (key)
    {
        #define CASE1(identifier) case sf::Keyboard::identifier: return #identifier; break;
        CASE1(Unknown);
		CASE1(A);
		CASE1(B);
		CASE1(C);
		CASE1(D);
		CASE1(E);
		CASE1(F);
		CASE1(G);
		CASE1(H);
		CASE1(I);
		CASE1(J);
		CASE1(K);
		CASE1(L);
		CASE1(M);
		CASE1(N);
		CASE1(O);
		CASE1(P);
		CASE1(Q);
		CASE1(R);
		CASE1(S);
		CASE1(T);
		CASE1(U);
		CASE1(V);
		CASE1(W);
		CASE1(X);
		CASE1(Y);
		CASE1(Z);
		CASE1(Num0);
		CASE1(Num1);
		CASE1(Num2);
		CASE1(Num3);
		CASE1(Num4);
		CASE1(Num5);
		CASE1(Num6);
		CASE1(Num7);
		CASE1(Num8);
		CASE1(Num9);
		CASE1(Escape);
		CASE1(LControl);
		CASE1(LShift);
		CASE1(LAlt);
		CASE1(LSystem);
		CASE1(RControl);
		CASE1(RShift);
		CASE1(RAlt);
		CASE1(RSystem);
		CASE1(Menu);
		CASE1(LBracket);
		CASE1(RBracket);
		CASE1(SemiColon);
		CASE1(Comma);
		CASE1(Period);
		CASE1(Quote);
		CASE1(Slash);
		CASE1(BackSlash);
		CASE1(Tilde);
		CASE1(Equal);
		CASE1(Dash);
		CASE1(Space);
		CASE1(Return);
		CASE1(BackSpace);
		CASE1(Tab);
		CASE1(PageUp);
		CASE1(PageDown);
		CASE1(End);
		CASE1(Home);
		CASE1(Insert);
		CASE1(Delete);
		CASE1(Add);
		CASE1(Subtract);
		CASE1(Multiply);
		CASE1(Divide);
		CASE1(Left);
		CASE1(Right);
		CASE1(Up);
		CASE1(Down);
		CASE1(Numpad0);
		CASE1(Numpad1);
		CASE1(Numpad2);
		CASE1(Numpad3);
		CASE1(Numpad4);
		CASE1(Numpad5);
		CASE1(Numpad6);
		CASE1(Numpad7);
		CASE1(Numpad8);
		CASE1(Numpad9);
		CASE1(F1);
		CASE1(F2);
		CASE1(F3);
		CASE1(F4);
		CASE1(F5);
		CASE1(F6);
		CASE1(F7);
		CASE1(F8);
		CASE1(F9);
		CASE1(F10);
		CASE1(F11);
		CASE1(F12);
		CASE1(F13);
		CASE1(F14);
		CASE1(F15);
		CASE1(Pause);
		default: return "Unknown"; break;
    }
}

sf::Keyboard::Key stringToKey(std::string const& str)
{
    #define CASE3(identifier) if (str == #identifier) { return sf::Keyboard::identifier; }
    CASE3(Unknown);
    CASE3(A);
    CASE3(B);
    CASE3(C);
    CASE3(D);
    CASE3(E);
    CASE3(F);
    CASE3(G);
    CASE3(H);
    CASE3(I);
    CASE3(J);
    CASE3(K);
    CASE3(L);
    CASE3(M);
    CASE3(N);
    CASE3(O);
    CASE3(P);
    CASE3(Q);
    CASE3(R);
    CASE3(S);
    CASE3(T);
    CASE3(U);
    CASE3(V);
    CASE3(W);
    CASE3(X);
    CASE3(Y);
    CASE3(Z);
    CASE3(Num0);
    CASE3(Num1);
    CASE3(Num2);
    CASE3(Num3);
    CASE3(Num4);
    CASE3(Num5);
    CASE3(Num6);
    CASE3(Num7);
    CASE3(Num8);
    CASE3(Num9);
    CASE3(Escape);
    CASE3(LControl);
    CASE3(LShift);
    CASE3(LAlt);
    CASE3(LSystem);
    CASE3(RControl);
    CASE3(RShift);
    CASE3(RAlt);
    CASE3(RSystem);
    CASE3(Menu);
    CASE3(LBracket);
    CASE3(RBracket);
    CASE3(SemiColon);
    CASE3(Comma);
    CASE3(Period);
    CASE3(Quote);
    CASE3(Slash);
    CASE3(BackSlash);
    CASE3(Tilde);
    CASE3(Equal);
    CASE3(Dash);
    CASE3(Space);
    CASE3(Return);
    CASE3(BackSpace);
    CASE3(Tab);
    CASE3(PageUp);
    CASE3(PageDown);
    CASE3(End);
    CASE3(Home);
    CASE3(Insert);
    CASE3(Delete);
    CASE3(Add);
    CASE3(Subtract);
    CASE3(Multiply);
    CASE3(Divide);
    CASE3(Left);
    CASE3(Right);
    CASE3(Up);
    CASE3(Down);
    CASE3(Numpad0);
    CASE3(Numpad1);
    CASE3(Numpad2);
    CASE3(Numpad3);
    CASE3(Numpad4);
    CASE3(Numpad5);
    CASE3(Numpad6);
    CASE3(Numpad7);
    CASE3(Numpad8);
    CASE3(Numpad9);
    CASE3(F1);
    CASE3(F2);
    CASE3(F3);
    CASE3(F4);
    CASE3(F5);
    CASE3(F6);
    CASE3(F7);
    CASE3(F8);
    CASE3(F9);
    CASE3(F10);
    CASE3(F11);
    CASE3(F12);
    CASE3(F13);
    CASE3(F14);
    CASE3(F15);
    CASE3(Pause);
    return sf::Keyboard::KeyCount;
}

KeyBinding::KeyBinding()
{
}

KeyBinding::~KeyBinding()
{
}

void KeyBinding::setKey(std::string const& id, sf::Keyboard::Key key)
{
    mKeys[id] = key;
}

sf::Keyboard::Key KeyBinding::getKey(std::string const& id)
{
    if (mKeys.find(id) == mKeys.end())
    {
        std::cerr << "KeyBinding : id (" << id << ") not recognized. " << std::endl;
        return sf::Keyboard::Unknown;
    }
    return mKeys.at(id);
}

std::string KeyBinding::getKeyString(std::string const& id)
{
    return keyToString(getKey(id));
}

bool KeyBinding::load(std::string const& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str()))
    {
        return false;
    }
    pugi::xml_node keys = doc.child("KeyBinding");
    if (keys)
    {
        for (pugi::xml_node key = keys.child("Key"); key; key = key.next_sibling("Key"))
        {
            std::string id = key.attribute("id").value();
            std::string k = key.attribute("key").value();

            mKeys[id] = stringToKey(k);
        }

        return true;
    }

    return false;
}

void KeyBinding::save(std::string const& filename)
{
    pugi::xml_document doc;
    doc.load_file(filename.c_str());
    if (doc.child("KeyBinding"))
    {
        doc.remove_child("KeyBinding");
    }
    pugi::xml_node keys = doc.append_child("KeyBinding");

    for (auto itr = mKeys.begin(); itr != mKeys.end(); itr++)
    {
        pugi::xml_node a = keys.append_child("Key");
        a.append_attribute("id") = itr->first.c_str();
        a.append_attribute("key") = keyToString(itr->second).c_str();
    }

    doc.save_file(filename.c_str());
}

} // namespace lp
