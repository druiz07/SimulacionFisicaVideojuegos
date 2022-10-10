
class SistemaParticulas
{
public:

	SistemaParticulas(Vector3 maxpos, Vector3 minpos, GeneradorSimple* g);
	void update(double t);





protected:
	std::list<Particula*>particulasGen;
	std::list<GeneradorSimple*>generadores;

};
SistemaParticulas::SistemaParticulas(Vector3 maxpos, Vector3 minpos, GeneradorSimple* g)
{

	generadores.push_back(g);


}
void SistemaParticulas::update(double t)
{

	for (auto i : generadores)
	{
		if (i != NULL) {
			auto aux = i->generateParticles();//Obrtenemos la lista de particulas
			for (auto a : aux)
			{
				particulasGen.push_back(a);
			}
		}
	}

	list<Particula*>::iterator it = particulasGen.begin();
	while (it != particulasGen.end())
	{
		(*it)->integrate(t);
		if (*it != NULL) {

			if (!(*it)->isAlive())
			{
				it = particulasGen.erase(it);
			}
			else it++;
		}
	}

}


