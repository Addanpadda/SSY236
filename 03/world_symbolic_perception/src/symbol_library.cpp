#include "world_symbolic_perception/symbol_library.hpp"

std::vector<std::string> symbol_names = {"on", "leftOf", "rightOf"};

bool SymbolLibrary::on(world_symbolic_perception::msg::Object obj1, 
		world_symbolic_perception::msg::Object obj2, 
		rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the on predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here
	
	//check if obj1 and 2 is the same
	if(obj1.name == obj2.name)
		return false;

	//boundarybox for obj2
	double obj2_min_x = obj2.pose.position.x - obj2.bbox.size.x/2.0;
	double obj2_max_x = obj2.pose.position.x + obj2.bbox.size.x/2.0;
	double obj2_min_y = obj2.pose.position.y - obj2.bbox.size.y/2.0;
	double obj2_max_y = obj2.pose.position.y + obj2.bbox.size.y/2.0;

	
	//check if obj1 is inside obj 2 boundarybox
	bool in_x = (obj1.pose.position.x >= obj2_min_x) && (obj1.pose.position.x =< obj2_max_x);
	bool in_y = (obj1.pose.position.y >= obj2_min_y) && (obj1.pose.position.y =< obj2_max_y);

	//check if obj1 is on top of obj 2
	
	double tol = 0.05;
	double top_obj2 = obj2.pose.position.z + obj2.bbox.size.z/2.0;
	double bottom_obj1 = obj.pose.position.z - obj2.bbox.size.z/2.0;
	bool on_z = std::abs(top_obj2-bottom_obj1)<=tol;

	//if inside x and y and on top of z return true otherwise false
	return in_x && in_y && on_z

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool SymbolLibrary::leftOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the leftOf predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool SymbolLibrary::rightOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the rightOf predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
