# Plinth
by Hapax

A foundation library of many helpful classes and functions.  
Includes an extension module of SFML-based classes and functions.

Requires C++11.

Welcome to Plinth!

Introduction

Plinth is a small library of classes and functions that help with generic tasks by providing string manipulation, multiple interpolation methods, animation tracks, simple random number generator, cubic Bezier calculator and more, including specific SFML stuff such as: extended list of named colours, common anchors of objects, image manipulation and even more!

Features

Main

Generic
All functions are templated.
Fully templated inclusion. Includes common functions such as min, max, swap, toggle, ordering two values and reading an integer from a series of bytes

Vectors
Fully templated. Defines vector types: Vector2 and Vector3, which can have any component type. They have alias shortcuts for doubles, unsigned ints, and signed ints

Ranges
Fully templated. Defines range types: Range (one-dimensional) and RangeArea (two-dimensional), which can have any component type. They have a number of useful methods such as three different clamps (clamp doesn't allow a value to be outside of the range), contains (tests to see if a value is in a range), overlaps (tests to see if another range overlaps the range)

Sizes
Fully templated. Defines simple, light-weight struct types: Size2 (contains x and y components) and Size3 (contains x, y and z components). Vectors and Ranges can convert to and from Sizes. Alias shortcuts do not include signed ints as a size cannot be negative. Sizes have a method to get the overall size: Size2 has getArea() and Size3 has getVolume()

Ascii
Header only.
List of constants for ascii codes. Multiple definitions based on the chosen list.

Bezier
Templated class.
Performs cubic bezier calculations using four control points.

Color
Colour classes/structs that include manipulation and conversion between types. Types include RGB, CMYK, HSL, and HSV. Rgb type can provide its relative luminance, its hex value, and can be constructed from: any other type in this inclusion, a value (including hexadecimals constants e.g. 0xffff00), a hexademical string, or a random colour (two types - rand()-based and Plinth's own Random-based)

File
Functions for basic loading and saving of - or just retrieving the size of - text or binary files.

Indexed Map
Templated class.
Container to allow an indexed map. Similar to std::map but also allows access through indices.

Math
All functions are templated.
Some generic mathematical functions and constants. Defines pi (as a double), and some other typed versions, converts radian to degrees and vice versa, returns the modulus of a floating point division, calculates the dot product of any matching pair of vectors.

Number Base
Converts from decimal (int) to hexadecimal (string) and vice versa.

Random
Small class that generates random numbers within a given range. A range can be stored and re-used or a temporary range can be specified at the time of generating a value. Uses <random> library and is set to Mersenne Twister 19937.

String From
Returns a string representation of a value in many types including Vectors, Ranges, Sizes, bool, and for everything not defined, returns the result of its std::to_string().

Strings
String manipulation functions such as: upper and lower case conversion, capitalisation, padding (left and/or right), trimming (left and/or right), replacing characters, "passwordify" a string, test if alphanumeric, concatenate a vector of strings into one string, formatting a string.

Tween
All functions are templated.
A number of different interpolation functions. Interpolates any type as long as they can use the required operators on the required types. Linear requires only multiplication with a POD (alpha) and addition to its own type. Eases in, out, or both.

Tween Piecewise
Templated class.
Allows piecewise linear interpolation of standard or custom types.

Tween Track
Templated class.
Allows piecewise linear, Bezier (easing) or step interpolation of types that are castable to double. Each node can have custom easing settings. Useful for individual parameters. Complex/custom types can be represented using multiple tracks, or Tween Tracks (TweenTrack2/TweenTrack3) - see below.

Tween Tracks
Templated classes.
Includes TweenTrack2 and TweenTrack3, which store two and three tracks (Tween Track above) respectively. Each track is a public member so can be accessed directly. Tracks can also be used together using the methods provided with these classes. For example, a node can be added to all tracks at once. A Plinth Vector2 or Vector3 can be returned from a specific position/time to retrieve the current state of all the tracks. Note that all tracks must be the same data type.

Additions

SFML

Generic
Get the length of a two- or three-dimensional sf::Vector, or its square (quicker), direct rounding of sf::Vector2s or sf::Vector3s, direct abs of sf::Vector2s or sf::Vector3s, test for intersection of lines, test if a point in inside a polygon, get a bounding box from a vector of vertices, change the alpha of a colour (using 0-255 or 0.f - 1.f), convert from sf::Vector2 or sf::Vector3 to pl::Vector and back, convert to sf::Color from pl::Color::Rgb, get sf::Color from a single value (will accept a large integer or a hexadecimal value e.g. sf::Color yellow = pl::Sfml::colorFromValue(0xffff00); ).

Anchor
Header only.
Get positions of corners or edge centres using either local or global bounds. Bounds are axis-aligned rectangles.

Animation
Includes Animation Tracks (specialised SFML versions of Plinth's Tween Track) and also preset Animation classes that contain animation tracks for SFML objects.

Colors
Header only.
This creates an extended list of sf::Color constants that includes many more colours than the SFML defaults.

Image
sf::Image manipulation functions such as clearing the image with a single colour while retaining its original transparency, conversion to greyscale, alpha manipulation.

Image Channel
Class that holds a single image channel separately from the image or other channels that allows single-channel manipulation. Includes manipulation methods.

Key Map
A class that stores a map of key controls and can be accessed via their string key or their index. The map can be modified at any time.

Resource Manager Basic
Basic resource manager for loading and storing sf::Fonts, sf::Images, sf::Textures and sf::SoundBuffers.

String From
Extends stringFrom() to include many SFML types: sf::Keyboard::Key, sf::VideoMode, sf::Color and both sf::Vector2 and sf::Vector3.

Information

Most of Plinth's functions/classes are in the pl namespace, although its full name (plinth) can also be used.

Plinth has two main lists of inclusion:
<Plinth/all.hpp and <Plinth/Sfml/all.hpp>
However, there are some shortcuts available:
<Plinth.hpp> = <Plinth/all.hpp>
<Plinth/Sfml.hpp> = <Plinth/Sfml/all.hpp>
<PlinthSfml.hpp> includes both <Plinth/all.hpp> and <Plinth/Sfml.hpp>
Note that <Plinth/Sfml.hpp> includes all of the Sfml additions, whereas <PlinthSfml.hpp> also includes the standard Plinth inclusions. Remember this: "PlinthSfml" = "Plinth" + "Sfml"

Plinth and Plinth/Sfml should be built separately or as separate modules/projects.

Plinth's main section has no external dependencies.
Plinth's SFML addition requires SFML.
Some of the examples may depend on external libraries.
