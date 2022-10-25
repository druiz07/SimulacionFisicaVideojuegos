
#include <list>
#include <random>
class Firework :public Particula
{


public:
	//virtual Particula* clone() const;
	std::list<Particula*> explode();
	Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri, float sizePart,int nDiv, Vector4 c = { 0.1,0.8,0.2,1 }, double tA = 5,int nGen=5,bool cV=false);
private:
	std::list<std::shared_ptr<GeneradorSimple> >gens_; //metodo que da generadores
	Vector3 actionSpace;
	Vector4 color;
	int nPart;
	int nGeneraciones;
	int sizeF;
	int tAlive;
	bool circulo = false;


};
Firework::Firework(Vector3 p, Vector3 initialSpeed, Vector3 a, float m, float d, RenderItem* ri,float sizePart, int nDiv, Vector4 c, double tA, int nP,bool cV)
 : Particula(p, initialSpeed, a, m, d, ri, { 1000,1000,1000 }, c, tA)
{
	actionSpace = { 1000,1000,1000 }; //Este espacio de accion es para 
	nGeneraciones = nDiv;
	nPart = nP;
	sizeF = sizePart;
	tAlive = tA;
	circulo = cV;

	//color = c;


}
std::list<Particula*> Firework::explode()
{
	random_device rand;
	default_random_engine generator = default_random_engine(rand());
	normal_distribution <double> normal{ 10,15 };
	std::list<Particula*>listExp;
	int nDivisiones = 20;

	float angle = 1;
	float radius = 3;
	if (nGeneraciones > 0) {
		for (int i = 0; i < nPart; i++)
		{
			Vector3 dir2{ (float)normal(generator),(float)normal(generator),(float)normal(generator) };
			Vector4 colorRand {(float)normal(generator),(float)normal(generator),(float)normal(generator),1};

			int offset = 1.25;
			int offsetCircle = 5;
			Vector3 pos = getPosition() * offset;
			if (circulo)
			{
				
				dir2= { float(physx::PxCos(angle) * radius), float(0), float(physx::PxSin(angle) * radius) };
				dir2 *= offsetCircle;
				angle += 360 / nPart;
			}

			//Aprovechar la posicion de firework para que parta mas o menos desde ahi
			Firework* p = new Firework(pos, dir2, { 0.5,0.5,0.5 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(sizeF)), Vector4(1, 0, 1, 1)), sizeF,nGeneraciones-1, colorRand, tAlive/1.25,nPart,circulo);
			listExp.push_back(p);
			

		}
		
	}
	return listExp;
}