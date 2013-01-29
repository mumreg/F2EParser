//
//  F2EParser.cpp
//  Flash2EngineParser
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#include "F2EParser.h"
#include <sstream>

template <typename T>
T StringToNumber (const string &Text ) //Text not by const reference so that the function can be used with a
{                                      //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

F2EParser::F2EParser()
{
    doc = new rapidxml::xml_document<>;
}

int F2EParser::parseBuffer(string *buffer)
{
    doc->parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>((char *)buffer->c_str());
    return 0;
}

int F2EParser::parseSprites(string *buffer, vector<F2ESprite> *sprites)
{
    parseBuffer(buffer);
    
    rapidxml::xml_node<> *curr_node = doc->first_node();
    curr_node = curr_node->first_node("TextureSheet")->first_node("Texture");
    
    string *attr_name;
    string *attr_value;
    
    for (; curr_node; curr_node = curr_node->next_sibling("Texture"))
    {
        F2ESprite sprite;
        resetSprite(&sprite);
        
        for (rapidxml::xml_attribute<> *attr = curr_node->first_attribute();
             attr; attr = attr->next_attribute())
        {
            attr_name = new string(attr->name());
            attr_value = new string(attr->value());
            saveAttrToSprite(attr_name, attr_value, &sprite);
            
            delete attr_name;
            delete attr_value;
        }
        
        sprites->push_back(sprite);
    }
    
    return 0;
}


int F2EParser::parseAnimations(string *buffer, vector<F2EAnimationPart> *animations)
{
    parseBuffer(buffer);
    
    rapidxml::xml_node<> *curr_node = doc->first_node();
    curr_node = curr_node->first_node("Animation");
    
    string *attr_name;
    string *attr_value;
    
    int framesCount = 0;
    
    for (; curr_node; curr_node = curr_node->next_sibling("Animation"))
    {
        F2EAnimationPart animationPart;
        
        //animationName
        rapidxml::xml_attribute<> *attr = curr_node->first_attribute();
        animationPart.animationName = string(attr->value());
        cout << "Animation name: " << animationPart.animationName << endl;
        
        //frameCount
        attr = attr->next_attribute();
        animationPart.frameCount = StringToNumber<int>(string(attr->value()));
        framesCount += animationPart.frameCount;
        
        //Getting parts
        rapidxml::xml_node<> *part_node = curr_node->first_node("Part");
        for (; part_node; part_node = part_node->next_sibling("Part"))
        {
            F2EPart part;
            attr = part_node->first_attribute();
            part.partName = string(attr->value());
            
            //Getting frames
            rapidxml::xml_node<> *frame_node = part_node->first_node("Frame");
            for (; frame_node; frame_node = frame_node->next_sibling("Frame"))
            {
                F2EFrame frame;
                resetFrame(&frame);
                
                for (attr = frame_node->first_attribute(); attr; attr = attr->next_attribute()) {
                    attr_name = new string(attr->name());
                    attr_value = new string(attr->value());
                    
                    saveAttrToFrame(attr_name, attr_value, &frame);
                    
                    delete attr_name;
                    delete attr_value;
                }
                
                part.frames.push_back(frame);
            }
            
            animationPart.parts.push_back(part);
        }
        
        animations->push_back(animationPart);
    }
    return framesCount;
}

void F2EParser::saveAttrToFrame(string *attr_name, string *attr_value, F2EFrame *frame)
{
    string name = *attr_name;
    string value = *attr_value;
    
    if (name == string("x"))
    {
        frame->x = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("y"))
    {
        frame->y = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("scaleX"))
    {
        frame->scaleX = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("scaleY"))
    {
        frame->scaleY = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("rotation"))
    {
        frame->rotation = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("index"))
    {
        frame->index = StringToNumber<int>(value);
        return;
    }
}

void F2EParser::saveAttrToSprite(string *attr_name, string *attr_value, F2ESprite *sprite)
{
    string name = *attr_name;
    string value = *attr_value;
    
    if (name == string("name"))
    {
        sprite->name = string(value);
        return;
    }
    
    if (name == string("width"))
    {
        sprite->width = StringToNumber<int>(value);
        return;
    }
    
    if (name == string("height"))
    {
        sprite->height = StringToNumber<int>(value);
        return;
    }
    
    if (name == string("path"))
    {
        sprite->path = string(*attr_value);
        return;
    }
    
    if (name == string("registrationPointX"))
    {
        sprite->anchorPointX = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("registrationPointY"))
    {
        sprite->anchorPointY = StringToNumber<float>(value);
        return;
    }
    
    if (name == string("zIndex"))
    {
        sprite->zIndex = StringToNumber<int>(value);
        return;
    }
}

void F2EParser::resetFrame(F2EFrame *frame)
{
    frame->x = 0;
    frame->y = 0;
    frame->rotation = 0;
    frame->scaleX = 0;
    frame->scaleY = 0;
    frame->index = 0;
}

void F2EParser::resetSprite(F2ESprite *sprite)
{
    sprite->zIndex = 0;
    sprite->width = 0;
    sprite->height = 0;
    sprite->anchorPointX = 0;
    sprite->anchorPointY = 0;
}

F2EParser::~F2EParser()
{
    delete doc;
}

