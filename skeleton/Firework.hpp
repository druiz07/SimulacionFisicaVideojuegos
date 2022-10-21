
#include <list>
class Firework :public Particula
{


public:
	int update(double t);
	//virtual Particula* clone() const;
	std::list<Particula*> explode();
	Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, std::list < std::shared_ptr<GeneradorSimple>>gS, Vector4 c = { 0.4,0.3,0.4,1 }, double tA = 5 );
private:
	std::list<std::shared_ptr<GeneradorSimple> >gens_; //metodo que da generadores
	Vector3 actionSpace;


};
Firework::Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri,   std::list< std::shared_ptr<GeneradorSimple>> gS, Vector4 c, double tA )
	: Particula(p, initialSpeed, a, m, d, ri, { 1000,1000,1000 }, c, tA)
{
	actionSpace = { 1000,1000,1000 }; //Este espacio de accion es para 

}
std::list<Particula*> Firework::explode()
{

	std::list<Particula*>listExp;
	for (auto i:gens_)
	{
		//Tanto la velocidad como la direccion sera aleatoria 
		Vector3 dir2{ -1,0,0 };
		int offset = 1.25;
		Vector3 pos=getPosition()*offset;

		//Aprovechar la posicion de firework para que parta mas o menos desde ahi
		Particula* p = new Particula(pos , dir2, { 0.0,0.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(2.25)), Vector4(1, 0, 1, 1)), actionSpace, Vector4{ 0.5,0.9,0.8,1 },5 );
		listExp.push_back(p);
	}
	return listExp;

}