
#include <iostream>
#include <string>
#include <vector>
#include "My2D.h"
#include <list>

MyPainter2D Obj_2D;

class GeomericObject {
public:

	int a_;
	int center_x= 75 , center_y= 150 ;
	int r_radius= 30;
	int center_x_=75 , center_y_=375;
	int x_edge=50, y_edge=50;
	
	void(GeomericObject::*callback_)(void) = 0;
	void exe() 
	{
		(this->*callback_)();
	}
	
	void drawCircle()
	{
		std::cout << "Draw Circle" <<a_<< std::endl;
		for (int a = 0; a <= 2 * r_radius; a++)
					{
						for (int b = 0; b <= 2 * r_radius; b++)
						{
							int f = (r_radius - b)*(r_radius - b) + (r_radius - a)*(r_radius - a) - r_radius*r_radius;
							if (f < 0 && -200 < f)
							{
								Obj_2D.drawPixel(center_x - r_radius + b, center_y - r_radius + a, 1.0f, 0.0f, 0.0f);
							}
						}
					}
	}

	void drawBox()
	{
		std::cout << "Draw Box" <<a_<< std::endl;
		Obj_2D.drawLine(center_x_ - x_edge / 2, center_y_ - y_edge / 2, center_x_ + x_edge / 2, center_y_ - y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x_ + x_edge / 2, center_y_ - y_edge / 2, center_x_ + x_edge / 2, center_y_ + y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x_ - x_edge / 2, center_y_ + y_edge / 2, center_x_ + x_edge / 2, center_y_ + y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x_ - x_edge / 2, center_y_ - y_edge / 2, center_x_ - x_edge / 2, center_y_ + y_edge / 2, 1.0f, 0.0f, 0.0f);
	}

	static GeomericObject* getPointer(const std::string type_name) {
		auto new_ob = new GeomericObject;
		if (type_name == "Box") {
			new_ob->callback_ = &GeomericObject::drawBox;
		}
		else if(type_name == "Circle"){
				new_ob->callback_ = &GeomericObject::drawCircle;
			}
		return new_ob;
	}
};

int main() {

	Obj_2D.initialize();

	while (Obj_2D.Close())
	{
		Obj_2D.preprocessing();


		std::list<GeomericObject*>go_list;
		go_list.push_back(GeomericObject::getPointer("Box"));
		go_list.push_back(GeomericObject::getPointer("Circle"));

		for (auto itr : go_list) {
			itr->exe();
		}

		for (auto itr : go_list) {
			delete itr;
		}

		GeomericObject my_box, my_circle;

		my_box.center_x_ = 75;
		my_box.center_y_ = 375;
		my_box.x_edge = 70;
		my_box.y_edge = 70;
		my_box.callback_ = &GeomericObject::drawBox;

		my_circle.center_x_ = 75;
		my_circle.center_y_ = 150;
		my_circle.x_edge = 30;
		my_circle.y_edge = 30;
		my_circle.callback_ = &GeomericObject::drawBox;

		my_box.exe();
		my_circle.exe();

		Obj_2D.postprocessiong();
	}
	return 0;
}