#include "CardSprite.h"

Vector <CardSprite*> *(CardSprite::card) = new Vector<CardSprite*> ();

Vector<CardSprite*> *CardSprite::getcard()
{
	return CardSprite::card;
}

bool CardSprite::initCardSprite()
{
	bool ret=false;
	if(Sprite::init())
	{
		bk = LayerColor::create( Color4B(200,200,200,255),96,96);
	    this->addChild(bk);

		int n = rand()%10;
		c_number = n==7 ? 4:2;
		switch ( c_number )  
		{  
		case 2: bk -> setColor(Color3B(244,179,194));    break;  
		case 4: bk -> setColor(Color3B(238,134,154));    break;  
		default:    break;  
		}

		labelnumber = Label::createWithTTF(StringUtils::format("%d",c_number), "fonts/HelloKitty.ttf", 50);
		labelnumber->setPosition(Point(48,48));
		labelnumber->setColor(Color3B::BLACK);
		bk->addChild(labelnumber);

		ret = true;
	}
	return ret;
}

CardSprite* CardSprite::createCardSprite()
{
	auto c = new CardSprite;
	c->initCardSprite();
	c->autorelease();
	card->pushBack(c);
	return c;
}

void CardSprite::moveTo(int r, int c)
{
	this->m_row = r;
	this->m_col = c;
	this->setPosition(Point(96*m_col+4*(m_col+1),96*m_row+4*(m_row+1)));
}

void CardSprite::doubleNumber() 
{    
    this->c_number = this->c_number*2;  
	
    
    //auto bk = this -> getChildByTag(101);  
    //Label *label = (Label *) bk -> getChildByTag(102);  
      
    // 对数字层的数字，重新绘制  
    labelnumber -> setString( StringUtils::format( "%d",c_number) );  
  
  
    //根据值得大小，对背景层重绘颜色  
    switch ( this -> c_number )  
    {  
    case 2:     bk -> setColor(Color3B(244,179,194));        break;  
    case 4:     bk -> setColor(Color3B(238,134,154));        break;  
    case 8:     bk -> setColor(Color3B(252,227,206));    labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 16:    bk -> setColor(Color3B(241,156,159)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 32:    bk -> setColor(Color3B(233,83,131)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 64:    bk -> setColor(Color3B(239,132,92));      labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 128:   labelnumber -> setScale(0.7f); bk -> setColor(Color3B(230,190,60)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 256:   labelnumber -> setScale(0.7f); bk -> setColor(Color3B(230,190,60)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 512:   labelnumber -> setScale(0.7f); bk -> setColor(Color3B(230,190,60)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    case 1024:  
    case 2048:  labelnumber -> setScale(0.5f); bk -> setColor(Color3B(210,180,30)); labelnumber -> setColor(Color3B(255,255,255))  ;break;  
    default:    break;  
    }  
}
