F2EParser
=========

Parser for exporting procedure animation from flash (xml from grapefrukt exporter) to your game engine.

For now I've just made a class for cocos2d (F2ECocos2d).

For now it supports: move, rotation, scaling (X and Y), alpha.

Usage - just open test project and look into code it's quite simple.

It looks for files Sc01_Anim.xml and Sc01_Sheet.xml, 
after that it looks for sprite sheet Sc01_Sheet.png and Sc01_Sheet.plist. If it doesn't succeed it looks for sprites
in single PNGs.

Video example of parser work: http://www.youtube.com/watch?v=KzYBzXZHTpk

For more information look into code.
Or you can try send e-mail to me: mumreg[at]gmail.com
