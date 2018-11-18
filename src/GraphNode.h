#include <Model.h>
#include <Transform.h>
#include <glm/glm.hpp>
class GraphNode
{
protected:
	GraphNode* parent;
	Model* model;
	glm::mat4* worldTransform;
	glm::mat4* transform;
	glm::mat4* transformOnStart;
	std::vector<GraphNode*> children;
	bool isRotating = true;
	float dir;
	float x;
	float y;
	float z;
public:
	GraphNode(bool _isRotating, Model* m = NULL)
	{
		isRotating = _isRotating;
		this->model = m;
		parent = NULL;
		transform = new glm::mat4(1);
		worldTransform = new glm::mat4(1);
		transformOnStart = new glm::mat4(1);
		const float MIN_RAND = -2.0, MAX_RAND = 2.0;
		const float range = MAX_RAND - MIN_RAND;
		dir = range * ((((float)rand()) / (float)RAND_MAX)) + MIN_RAND;
		x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
	~GraphNode(void) 
	{
		delete transform;
		delete worldTransform;
		for (unsigned int i = 0; i < children.size(); ++i) {
			delete children[i];
		}
	}
	void SetTransform(glm::mat4* matrix) 
	{ 
		transform = matrix; 
		*transformOnStart = *transform;
	}
	
	glm::mat4* GetTransform() { return transform; }
	
	glm::mat4* GetWorldTransform() { return worldTransform; }
	
	Model* GetModel() { return model; }
	
	void SetModel(Model* m) { model = m; }
	
	void AddChild(GraphNode* node) 
	{
		children.push_back(node);
		node->parent = this;
	}
	virtual void Update(float msec) 
	{
		*transform = glm::rotate(*transform, glm::radians(10.0f) * msec, glm::vec3(0, 1, 0));
		if (parent) 
		{
			*worldTransform = *parent->worldTransform * (*transform);
			/*std::cout << "Graph Node" << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					float* tmp = glm::value_ptr(worldTransform[i][j]);
					std::cout << *tmp << " ";
				}
				std::cout << std::endl;
			}*/
			if(!isRotating)
			{
				*worldTransform = *parent->worldTransform * (*transformOnStart);
			}
		}
		else 
		{
			*worldTransform = *transform;
		}
		if (model) 
		{
			if (!parent && !isRotating) 
			{
				model->setTransform(transformOnStart);
			}
			else {
				model->setTransform(worldTransform);
			}
		}
		for (GraphNode* node : children) 
		{
			node->Update(msec);
		}
	}
	virtual void Draw() 
	{
		if (model) { model->Draw(); }

		for (GraphNode* node : children)
		{
			node->Draw();
		}
	}
};