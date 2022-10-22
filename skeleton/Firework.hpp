
#include <list>
#include <random>
class Firework :public Particula
{


public:
	//virtual Particula* clone() const;
	std::list<Particula*> explode();
	Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, float sizePart,int nDiv, Vector4 c = { 0.1,0.8,0.2,1 }, double tA = 5,int nGen=5);
private:
	std::list<std::shared_ptr<GeneradorSimple> >gens_; //metodo que da generadores
	Vector3 actionSpace;
	int nPart;
	int nGeneraciones;
	int sizeF;
	int tAlive;


};
Firework::Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri,float sizePart, int nDiv, Vector4 c, double tA, int nP)
 : Particula(p, initialSpeed, a, m, d, ri, { 1000,1000,1000 }, c, tA)
{
	actionSpace = { 1000,1000,1000 }; //Este espacio de accion es para 
	nGeneraciones = nDiv;
	nPart = nP;
	sizeF = sizePart;
	tAlive = tA;

}
std::list<Particula*> Firework::explode()
{
	random_device rand;
	default_random_engine generator = default_random_engine(rand());
	normal_distribution <double> normal{ 10,15 };
	std::list<Particula*>listExp;
	int nDivisiones = 20;

	if (nGeneraciones > 0) {
		for (int i = 0; i < nPart; i++)
		{
			Vector3 dir2{ (float)normal(generator),(float)normal(generator),(float)normal(generator) };

			int offset = 1.25;
			Vector3 pos = getPosition() * offset;

			//Aprovechar la posicion de firework para que parta mas o menos desde ahi
			Firework* p = new Firework(pos, dir2/3, { 0.0,0.0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(sizeF)), Vector4(1, 0, 1, 1)), sizeF,nGeneraciones-1, Vector4{ 0.5,0.9,0.8,1 }, tAlive/1.25,nPart);
			listExp.push_back(p);


		}
		
	}
	return listExp;
}