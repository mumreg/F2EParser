//
//  F2EParser.cpp
//  Flash2EngineParser
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#include "F2EParser.h"
#include <cstdlib>

F2EParser::F2EParser()
{
    m_doc = std::shared_ptr<rapidxml::xml_document<>>(new rapidxml::xml_document<>());
}

int F2EParser::parseBuffer(const string &buffer)
{
    m_doc->parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(const_cast<char *>(buffer.c_str()));
    return 0;
}

int F2EParser::parseSprites(const string &buffer, vector<std::shared_ptr<F2ESprite>> &sprites)
{
    parseBuffer(buffer);
    
    rapidxml::xml_node<> *curr_node = m_doc->first_node();
    curr_node = curr_node->first_node("TextureSheet")->first_node("Texture");
    
    for (; curr_node; curr_node = curr_node->next_sibling("Texture"))
    {
        auto sprite = std::shared_ptr<F2ESprite>(new F2ESprite());
        for (auto attr = curr_node->first_attribute(); attr; attr = attr->next_attribute()) {
            saveAttrToSprite(attr->name(), attr->value(), sprite);
        }
        
        sprites.push_back(sprite);
    }
    
    return 0;
}


int F2EParser::parseAnimations(const string &buffer, vector<std::shared_ptr<F2EAnimationPart>> &animations)
{
    parseBuffer(buffer);
    
    rapidxml::xml_node<> *curr_node = m_doc->first_node();
    curr_node = curr_node->first_node("Animation");
    
    int framesCount = 0;
    
    for (; curr_node; curr_node = curr_node->next_sibling("Animation"))
    {
        auto animationPart = std::shared_ptr<F2EAnimationPart>(new F2EAnimationPart());
        
        //animationName
        rapidxml::xml_attribute<> *attr = curr_node->first_attribute();
        animationPart->animationName = string(attr->value());
#ifdef F2E_DEBUG
        cout << "Animation name: " << animationPart->animationName << endl;
#endif
        
        //frameCount
        attr = attr->next_attribute();
        animationPart->frameCount = atoi(attr->value());
        framesCount += animationPart->frameCount;
        
        //Getting parts
        rapidxml::xml_node<> *part_node = curr_node->first_node("Part");
        for (; part_node; part_node = part_node->next_sibling("Part"))
        {
            auto part = std::shared_ptr<F2EPart>(new F2EPart());
            attr = part_node->first_attribute();
            part->partName = string(attr->value());
            
            //Getting frames
            rapidxml::xml_node<> *frame_node = part_node->first_node("Frame");
            for (; frame_node; frame_node = frame_node->next_sibling("Frame"))
            {
                auto frame = std::shared_ptr<F2EFrame>(new F2EFrame());
                for (attr = frame_node->first_attribute(); attr; attr = attr->next_attribute()) {
                    saveAttrToFrame(attr->name(), attr->value(), frame);
                }
                
                part->frames.push_back(frame);
            }
            
            animationPart->parts.push_back(part);
        }
        
        animations.push_back(animationPart);
    }
    return framesCount;
}

void F2EParser::saveAttrToFrame(const std::string &attr_name, const std::string &attr_value, std::shared_ptr<F2EFrame> &frame)
{
    string name = attr_name;
    const char *value = attr_value.c_str();
    
    if (name == string("x"))
    {
        frame->x = atof(value);
        return;
    }
    
    if (name == string("y"))
    {
        frame->y = atof(value);
        return;
    }
    
    if (name == string("scaleX"))
    {
        frame->scaleX = atof(value);
        return;
    }
    
    if (name == string("scaleY"))
    {
        frame->scaleY = atof(value);
        return;
    }
    
    if (name == string("rotation"))
    {
        frame->rotation = atof(value);
        return;
    }
    
    if (name == string("index"))
    {
        frame->index = atoi(value);
        return;
    }
    
    if (name == string("alpha"))
    {
        frame->opacity = atof(value);
        return;
    }
}

void F2EParser::saveAttrToSprite(const string &name, const string &attr_value, std::shared_ptr<F2ESprite> &sprite)
{
    const char *value = attr_value.c_str();
    if (name == string("name"))
    {
        sprite->name = attr_value;
        return;
    }
    
    if (name == string("width"))
    {
        sprite->width = atoi(value);
        return;
    }
    
    if (name == string("height"))
    {
        sprite->height = atoi(value);
        return;
    }
    
    if (name == string("path"))
    {
        sprite->path = attr_value;
        return;
    }
    
    if (name == string("registrationPointX"))
    {
        sprite->anchorPointX = atof(value);
        return;
    }
    
    if (name == string("registrationPointY"))
    {
        sprite->anchorPointY = atof(value);
        return;
    }
    
    if (name == string("zIndex"))
    {
        sprite->zIndex = atoi(value);
        return;
    }
}

F2EParser::~F2EParser()
{
}
