#include "GameScene.h"
#include "CardSprite.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	Size visiblesize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("540.jpg");
	bg->setPosition(Vec2(visiblesize.width/2, visiblesize.height/2));
	addChild(bg);

	//layercolor层
	colorBack = LayerColor::create
		( Color4B(255,255,255,255),
		96*4+4*5, 96*4+4*5
		);
	colorBack->ignoreAnchorPointForPosition(false);
	colorBack->setAnchorPoint(Point(0.5,0.5));

	colorBack->setPosition(Point(visiblesize.width/2, visiblesize.height/2));
	this->addChild(colorBack);
	/*
	LayerGradient* layergradient = LayerGradient::create
		(Color4B(0,255,0,0),Color4B(0,0,255,255));
	addChild(layergradient);
	*/
	//在colorback层上面加层
	for(int row=0; row<4; ++row)
	{
		for(int col=0; col<4; ++col)
		{
			layerTiled = LayerColor::create(
				Color4B(238,134,154,80),
				96,96);
			layerTiled->setPosition(Point(96*col+4*(col+1),96*row+4*(row+1)));
			colorBack->addChild(layerTiled);
		}
	}

	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			map[i][j]=0;
		}
	}
	CardSprite::card->clear();
	createCardSprite();

	

	title = Label::createWithTTF("2 0 4 8","fonts/HelloKitty.ttf",100);
	title->setPosition(Point(visiblesize.width/2 - 60, visiblesize.height - 200));
	addChild(title);

	scorelayer = LayerColor::create
		( Color4B(238,134,154,255),
		96*2+4, 96+32
		);
	scorelayer->ignoreAnchorPointForPosition(false);
	scorelayer->setAnchorPoint(Point(0.5,0.5));
	scorelayer->setPosition(Point(visiblesize.width/2 - 101, visiblesize.height/6 - 4*2));
	this->addChild(scorelayer);

	score =0;
	Score = Label::createWithTTF("Score", "fonts/HelloKitty.ttf", 40);
	Score->setPosition(Point(scorelayer->getContentSize().width/2,scorelayer->getContentSize().height - Score->getContentSize().height/2));
	scorelayer->addChild(Score);
	if(score>=10000)
		labelfontsize = 50;
	else
		labelfontsize = 60;
	labelscore = Label::createWithTTF("0", "fonts/HelloKitty.ttf", labelfontsize);
	labelscore->setPosition(Point(scorelayer->getContentSize().width/2,scorelayer->getContentSize().height/2 - labelscore->getContentSize().height/2));
	scorelayer->addChild(labelscore);

	bestlayer = LayerColor::create
		( Color4B(238,134,154,255),
		96*2+4, 96+32
		);
	bestlayer->ignoreAnchorPointForPosition(false);
	bestlayer->setAnchorPoint(Point(0.5,0.5));
	bestlayer->setPosition(Point(visiblesize.width/2 + 101, visiblesize.height/6 - 4*2));
	this->addChild(bestlayer);

	Best = Label::createWithTTF("Best", "fonts/HelloKitty.ttf", 40);
	Best->setPosition(Point(bestlayer->getContentSize().width/2,bestlayer->getContentSize().height - Best->getContentSize().height/2));
	bestlayer->addChild(Best);
	if(bestScore>=10000)
		bestfontsize = 50;
	else
		bestfontsize = 60;
	bestScore = UserDefault::getInstance()->getIntegerForKey("BEST");

	bestscore = Label::createWithTTF( StringUtils::format(" %d  ",bestScore), "fonts/HelloKitty.ttf",bestfontsize);
	bestscore->setPosition(Point(bestlayer->getContentSize().width/2,bestlayer->getContentSize().height/2 - bestscore->getContentSize().height/2));
	bestlayer->addChild(bestscore);

	//endmenu
	endmenu = MenuItemImage::create("endmenu.png","endmenu.png",CC_CALLBACK_0(GameScene::endScene,this));
	endmenu->setPosition(Point(visiblesize.width/2 + title->getContentSize().width/2, visiblesize.height - 200));
	auto menu = Menu::create(endmenu,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//添加触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), title);

	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode)     
	{         //监听返回键        
	case EventKeyboard::KeyCode::KEY_ESCAPE:              
		Director::getInstance()->end();             
		break;         
		//监听menu键        
	case EventKeyboard::KeyCode::KEY_MENU:             
		break;     
	} 
}

void GameScene::endScene()
{
//	Director::getInstance() -> replaceScene(CCTransitionFadeDown::create(0.5f,GameScene::createScene()));
	endlayer = LayerColor::create
		( Color4B(255,255,255,0),
		64*4, 64*5
		);
	endlayer->ignoreAnchorPointForPosition(false);
	endlayer->setAnchorPoint(Point(0.5,0.5));
	endlayer->setPosition(Point(Director::getInstance()->getWinSize().width/2 , Director::getInstance()->getWinSize().height/2));
	this->addChild(endlayer);

	endsprite = Sprite::create("endscene1.png");
	endsprite->setAnchorPoint(Point(0.5,0.5));
	endsprite->setPosition(Point(endlayer->getContentSize().width / 2, endlayer->getContentSize().height/2));
	endlayer->addChild(endsprite);

	restartBtn = Label::createWithTTF("Restart", "fonts/HelloKitty.ttf", 60);
	restartBtn->setColor(Color3B(255, 255, 255));
	//restartBtn->setPosition(Point(endlayer->getContentSize().width / 2,8* endlayer->getContentSize().height/12));
	///endlayer->addChild(restartBtn);
	restartmenu = MenuItemLabel::create(restartBtn,CC_CALLBACK_0(GameScene::restartgame,this));
	restartmenu->setPosition(Point(endlayer->getContentSize().width / 2,8* endlayer->getContentSize().height/12));

	endBtn = Label::createWithTTF("Exit", "fonts/HelloKitty.ttf", 60);
	endBtn->setColor(Color3B(255, 255, 255));
	exitmenu = MenuItemLabel::create(endBtn,CC_CALLBACK_0(GameScene::endgame,this));
	exitmenu->setPosition(Point(endlayer->getContentSize().width / 2,4* endlayer->getContentSize().height/12));

	cancerBtn = Label::createWithTTF("Cancer", "fonts/HelloKitty.ttf", 60);
	cancerBtn->setColor(Color3B(255, 255, 255));
	cancermenu = MenuItemLabel::create(cancerBtn,CC_CALLBACK_0(GameScene::regame,this));
	cancermenu->setPosition(Point(endlayer->getContentSize().width / 2, endlayer->getContentSize().height/12 - cancerBtn->getContentSize().height/2));

	auto menu = Menu::create(restartmenu, exitmenu, cancermenu, NULL);
	menu->setPosition(Vec2::ZERO);
	endlayer->addChild(menu);

}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	 startpt = touch -> getLocation();   
	 m_startMove = true;
	 if(title->getBoundingBox().containsPoint(startpt))
	 {
		 Director::getInstance()->replaceScene(CCTransitionFadeDown::create(0.5f,MainScene::createScene()));
	 }
	 
	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{ 
     endpt = touch -> getLocation(); 

	 if( m_startMove==true && ( abs( startpt.x - endpt.x ) > 10 || abs( startpt.y - endpt.y ) >10 ))  
		{  
            m_startMove = false;  
			m_sound_clear = false;
			judgegame();
            // 根据起末坐标位置，判断向哪个方向移动  
            if( abs(startpt.x - endpt.x ) > abs(startpt.y - endpt.y) )  
            {  
                if( startpt.x > endpt.x ) 
				{
					if(ismoveleft==true)
					{
						moveLeft(); 
						createCardSprite();
						judgegame();
						//log("left");
					}
				}
                else if(startpt.x < endpt.x )
				{  
					if(ismoveright==true)
					{
						moveRight();
						createCardSprite();
						judgegame();
						//log("right");
					}
				}
            }  
            else  
            {  
                if( startpt.y < endpt.y )
				{
					if(ismoveup==true)
					{
						moveUp(); 
						createCardSprite();
						judgegame();
						//log("up");
					}
				}
                else  
				{
					if(ismovedown==true)
					{
						moveDown(); 
						createCardSprite();
						judgegame();
						//log("down");
					}
				}
            }  
		
        }  
}

void GameScene::judgegame()
{
	judgemove();

	

	if( m_sound_clear )
	{
		SimpleAudioEngine::getInstance() -> playEffect("move.mp3");
	}


	if(!ismoveup && !ismovedown && !ismoveleft && !ismoveright)
	{
		endScene();
	}
}

void GameScene::judgemove()
{
	
	ismoveleft = false;
	ismoveright = false;
	ismoveup = false;
	ismovedown = false;

	//up
	for(int r=0; r <GAME_ROWS-1; r++)
	{
		for(int l=0; l <=GAME_COLS-1; l++)
		{
			if(map[r+1][l]==0)
			{
				if(map[r][l]!=0)
				{
					ismoveup = true;
					break;
				}
			}
			else
			{
				if(map[r][l]!=0)
				{
					if(CardSprite::card->at(map[r][l]-1)->c_number == CardSprite::card->at(map[r+1][l]-1)->c_number)
					{
						ismoveup = true;
						break;
					}
				}
			}
		}
		if( ismoveup == true  )   break;  
	}

	//down
	for(int r=GAME_ROWS-1; r > 0; r--)
	{
		for(int l=0; l <= GAME_COLS-1; l++)
		{
			if(map[r-1][l]==0)
			{
				if(map[r][l]!=0)
				{
					ismovedown = true;
					break;
				}
			}
			else
			{
				if(map[r][l]!=0)
				{
					if(CardSprite::card->at(map[r][l]-1)->c_number == CardSprite::card->at(map[r-1][l]-1)->c_number)
					{
						ismovedown = true;
						break;
					}
				}
			}
		}
		if( ismovedown == true  )   break;  
	}

	//left
	for(int l=GAME_COLS-1; l > 0; l--)
	{
		for(int r=0; r <= GAME_ROWS-1; r++)
		{
			if(map[r][l-1]==0)
			{
				if(map[r][l]!=0)
				{
					ismoveleft = true;
					break;
				}
			}
			else
			{
				if(map[r][l]!=0)
				{
					if(CardSprite::card->at(map[r][l]-1)->c_number == CardSprite::card->at(map[r][l-1]-1)->c_number)
					{
						ismoveleft = true;
						break;
					}
				}
			}
		}
		if( ismoveleft == true  )   break;  
	}

	//right
	for(int l=0; l < GAME_COLS-1; l++)
	{
		for(int r=0; r <= GAME_ROWS-1; r++)
		{
			if(map[r][l+1]==0)
			{
				if(map[r][l]!=0)
				{
					ismoveright = true;
					break;
				}
			}
			else
			{
				if(map[r][l]!=0)
				{
					if(CardSprite::card->at(map[r][l]-1)->c_number == CardSprite::card->at(map[r][l+1]-1)->c_number)
					{
						ismoveright = true;
						break;
					}
				}
			}
		}
		if( ismoveright == true  )   break;  
	}
	
}

void GameScene::moveUp()
{
	for( int col = 0 ; col < 4 ; ++col )  
    {  
		int row_w = 3;
        for( int row = 3 ; row >= 0 ; --row )  
        {  
            if( map[row][col] > 0 ) 	
            {	
				
				//log("map[row %d][col %d]=%d",row,col,map[row][col]);
                for( int row1 = row ; row1 < row_w ; ++row1 )  
                {  
                    // 上方是空的  才会移动  
                    if( map[row1+1][col] == 0 )  
                    {  //log("map[row1 %d][col %d]=%d",row1,col,map[row1][col]);
                        map[row1+1][col] = map[row1][col];  
						//log("map[row1 %d][col %d]=%d",row1+1,col,map[row1+1][col]);
                        map[row1][col] = 0; 
						
  
						CardSprite::card->at( map[row1+1][col] - 1 ) -> moveTo( row1+1 , col );  
                    }  
                    else  
                    {  
                        int numObj = CardSprite::card->at( map[row1+1][col] - 1 ) -> c_number;  //获取上面放个数字

                        int numNow = CardSprite::card->at( map[row1][col] - 1 ) -> c_number;  //获取当前放个数字
                          
                        // 两个格子数字相同  
                        if( numNow == numObj )  
                        {  
							m_sound_clear = true;
							score += numObj*2;
							labelscore->setString( StringUtils::format(" %d  ",score));
							if (score > bestScore)
							{
								bestScore = score;
								UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
							}
							bestscore->setString( StringUtils::format(" %d  ",bestScore));

                            // 上面那一行数字X2
                            CardSprite::card->at( map[row1+1][col] - 1 ) -> doubleNumber();  
                            // 去除掉当前数字块  
                            CardSprite::card->at( map[row1][col] - 1 ) -> removeFromParent();  
                            // 获取当前数字块编号  
                            int index = map[row1][col];  
                            CardSprite::card->erase( map[row1][col] - 1 );  
                            // 纠正所有大于index号码的编号大小  
                            for( int r = 0 ; r < 4 ; ++r )  
                            {  
                                for( int c = 0 ; c < 4 ; ++c )  
                                {  
                                    if( map[r][c] > index )  
                                    {  
                                        --map[r][c];  
                                    }  
                                }  
                            }  
                            // 将当前块编号设置为0  
                            map[row1][col] = 0;  
                        } 
						row_w--; 
                        break; 
                    }  
					
                } 
				
			}  
        }  
    }  
}

void GameScene::moveDown( )
{
	// 向下移动所有的块
	for( int col = 0 ; col < 4 ; ++col )
	{
		int row_w = 0;
		for( int row = 0 ; row < 4 ; ++row )
		{
			if( map[row][col] > 0 )
			{
				for( int row1 = row ; row1 > row_w ; --row1 )
				{
					if( map[row1-1][col] == 0 )
					{
						map[row1-1][col] = map[row1][col];
						map[row1][col] = 0;
						CardSprite::card->at( map[row1-1][col] - 1 ) -> moveTo( row1-1 , col );
					}
					else
					{
						int numObj = CardSprite::card->at( map[row1-1][col] - 1 ) -> c_number;
						int numNow = CardSprite::card->at( map[row1][col] - 1 ) -> c_number;
						if( numNow == numObj )
						{
							m_sound_clear = true;
							score += numObj*2;
							labelscore->setString( StringUtils::format(" %d  ",score));
							if (score > bestScore)
							{
								bestScore = score;
								UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
							}
							bestscore->setString( StringUtils::format(" %d  ",bestScore));
							CardSprite::card->at( map[row1-1][col] - 1 ) -> doubleNumber();
							CardSprite::card->at( map[row1][col] - 1 ) -> removeFromParent();

							int index = map[row1][col];
							CardSprite::card->erase( map[row1][col] - 1 );

							// 纠正块的编号
							for( int r = 0 ; r < 4 ; ++r )
							{
								for( int c = 0 ; c < 4 ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row1][col] = 0;
						}
						row_w++;
						break;
					}
				}
			}
		}
	}
}

void GameScene::moveLeft( )
{
	// 向左移动所有的块
	for( int row = 0 ; row < 4 ; ++row )
	{
		int col_l = 0;
		for( int col = 0 ; col < 4 ; ++col )
		{
			if( map[row][col] > 0 )
			{
				for( int col1 = col ; col1 > col_l ; --col1 )
				{
					if( map[row][col1-1] == 0 )
					{
						map[row][col1-1] = map[row][col1];
						map[row][col1] = 0;

						CardSprite::card->at( map[row][col1-1] - 1 ) -> moveTo( row , col1-1 );
					}
					else
					{
						int numObj = CardSprite::card->at( map[row][col1-1] - 1 ) -> c_number;
						int numNow = CardSprite::card->at( map[row][col1] - 1 ) -> c_number;
						if( numNow == numObj )
						{
							m_sound_clear = true;
							score += numObj*2;
							labelscore->setString( StringUtils::format(" %d  ",score));
							if (score > bestScore)
							{
								bestScore = score;
								UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
							}
							bestscore->setString( StringUtils::format(" %d  ",bestScore));

							CardSprite::card->at( map[row][col1-1] - 1 ) -> doubleNumber();
							CardSprite::card->at( map[row][col1] - 1 ) -> removeFromParent();
							int index = map[row][col1];
							CardSprite::card->erase( map[row][col1] - 1 );
							// 纠正块的编号
							for( int r = 0 ; r < 4 ; ++r )
							{
								for( int c = 0 ; c < 4 ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row][col1] = 0;
						}
						col_l++;
						break;
					}
				}
			}
		}
	}
}

void GameScene::moveRight( )
{
	// 向右移动所有的块
	for( int row = 0 ; row < 4 ; ++row )
	{
		int col_l = 3;
		for( int col = 4 - 1 ; col >= 0 ; --col )
		{
			if( map[row][col] > 0 )
			{
				for( int col1 = col ; col1 < col_l ; ++col1 )
				{
					if( map[row][col1+1] == 0 )
					{
						map[row][col1+1] = map[row][col1];
						map[row][col1] = 0;

						CardSprite::card->at( map[row][col1+1] - 1 ) -> moveTo( row , col1+1 );
					}
					else
					{
						int numObj = CardSprite::card->at( map[row][col1+1] - 1 ) -> c_number;
						int numNow = CardSprite::card->at( map[row][col1] - 1 ) -> c_number;
						if( numNow == numObj )
						{
							m_sound_clear = true;
							score += numObj*2;
							labelscore->setString( StringUtils::format(" %d  ",score));
							if (score > bestScore)
							{
								bestScore = score;
								UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
							}
							bestscore->setString( StringUtils::format(" %d  ",bestScore));

							CardSprite::card->at( map[row][col1+1] - 1 ) -> doubleNumber();
							CardSprite::card->at( map[row][col1] - 1 ) -> removeFromParent();				
							int index = map[row][col1];
							CardSprite::card->erase( map[row][col1] - 1 );

							for( int r = 0 ; r < 4 ; ++r )
							{
								for( int c = 0 ; c < 4 ; ++c )
								{
									if( map[r][c] > index )
									{
										--map[r][c];
									}
								}
							}
							map[row][col1] = 0; 
						}
						col_l--;
						break;
					}
				}
			}
		}
	}
}

void GameScene::createCardSprite()
{
	auto c_card = CardSprite::createCardSprite();
	
	int freeCount = 16 - CardSprite::card->size();
	//log("%d",freeCount);
	int num = 0;
	if(freeCount!=0)
	num = rand()%freeCount;//在最大的可用空间随机生成一个数
	int row, col, count=0;
	bool find = false;

	for(row=0; row<GAME_ROWS ; ++row)
	{
		for(col=0; col<GAME_COLS ; ++col)//从第一个位置开始遍历，到最后一个位置
		{
			if(map[row][col]==0)
			{
				++count;//遇到空位置就++
				if(count >= num)//若遇到大于产生的随机数，即把数字块放在那
				{
					//log("count %d",count);
					find = true;
					break;
				}
			}
		}
		if(find) 
			break;
	}
		colorBack->addChild(c_card);
		c_card->moveTo(row,col);
		map[row][col]=CardSprite::card->getIndex(c_card)+1;
		//log("map[%d][%d] = %d",row, col, map[row][col]);

}

void GameScene::restartgame()
{
	Director::getInstance() -> replaceScene(CCTransitionFadeDown::create(0.5f,GameScene::createScene()));
}

void GameScene::endgame()
{
	Director::getInstance()->end();
}

void GameScene::regame()
{
	endlayer->removeAllChildren();
}
