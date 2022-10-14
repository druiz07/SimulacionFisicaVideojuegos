
#include <time.h>
#include <random>

class Uniforme : public GeneradorSimple
{

public:
	Uniforme(Vector3 devvel, Vector3 dp, Vector3 pWidth, Vector3 velWidth, std::string n, Vector3 mp, Vector3 mv, Vector4 pc, int np, int tA);
	list<Particula*> generateParticles() override;
	bool checkSpace();
	~Uniforme();

protected:

	Vector3 devpos;
	Vector3 devvel;
	Vector4 particlecolor;
	Vector3 pos_width;
	Vector3 vel_width;
	std::mt19937 e2;
	int nPart;
	float gravity = -10.0;
	int timeAlive;
	int probability;
	

	std::uniform_real_distribution<double>d{ 0,1 }; //Multiplicado por la varianza y sumas la media 


};
inline Uniforme::Uniforme(Vector3 dv, Vector3 dp, Vector3 pWidth, Vector3 velWidth,std::string n, Vector3 mp, Vector3 mv, Vector4 pc, int np, int tA):GeneradorSimple(n)
{
	devpos = dp;
	devvel = dv;
	pos_width = pWidth;
	vel_width = velWidth;
	mediaPos = mp;
	mediaVel = mv;
	particlecolor = pc;
	nPart = np;
	timeAlive = tA;
	std::random_device r{};
	e2 = std::mt19937(r());

}
list<Particula*>Uniforme::generateParticles()
{
	std::list<Particula*> pAux;

	for (int i = 0; i < nPart; i++)
	{
		int prob = d(e2);
		if (prob > probability)continue;
		
		auto px = std::uniform_real_distribution<float>(mediaPos.x - pos_width.x / 2, mediaPos.x + pos_width.x / 2);
		auto py = std::uniform_real_distribution<float>(mediaPos.y - pos_width.y / 2, mediaPos.y + pos_width.y / 2);
		auto pz = std::uniform_real_distribution<float>(mediaPos.z - pos_width.z / 2, mediaPos.z + pos_width.z / 2);

		auto vx = std::uniform_real_distribution<float>(mediaVel.x - vel_width.x / 2, mediaVel.x + vel_width.x / 2);
		auto vy = std::uniform_real_distribution<float>(mediaVel.y - vel_width.y / 2, mediaVel.y + vel_width.y / 2);
		auto vz = std::uniform_real_distribution<float>(mediaVel.z - vel_width.z / 2, mediaVel.z + vel_width.z / 2);

		Vector3 pos_result = { (px(e2)),(py(e2)), (pz(e2)) };
		Vector3  vel_result = { (vx(e2)), (vy(e2)), (vz(e2)) };

		auto p = new Particula();
		p->setParticle(pos_result, vel_result, { 0.0,0,0.0 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(0.9)), Vector4(1, 0, 1, 1)), timeAlive, particlecolor);
		pAux.push_back(p);


	}
	return pAux;

}
inline bool Uniforme::checkSpace()
{
	
}
Uniforme::~Uniforme()
{

}