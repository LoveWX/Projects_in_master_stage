#ifndef _MATRIX_H_
#define _MATRIX_H_

class matrix {
private:
	int Nr, Nc;
	double** p; 
	void delete_all() {
		for (int i = 0; i < Nr; i++) 
			delete[] p[i];
		delete[] p;
	}
public:
	matrix() 
	{
		Nr = 1, Nc = 1;
		p = new double*[Nr];
		for(int i = 0; i < Nr; i++)
			p[i] = new double[Nc];
		p[0][0]=1.; 
	};
	matrix(int i, int j) 
	{
		Nr = i, Nc = j;

		p = new double*[Nr];
		for(i = 0; i < Nr; i++)
			p[i] = new double[Nc];
	};
	matrix(matrix& b) {
		Nr = b.Nr;
		Nc = b.Nc;
		p = new double*[Nr];
		for (int i = 0; i < Nr; i++) {
			p[i] = new double[Nc];
			for (int j = 0; j < Nc; j++) {
				p[i][j] = b[i][j];
			}
		}
	}
	void init(int i, int j) 
	{
		delete_all();
		Nr = i, Nc = j;
		p = new double*[Nr];
		for(i = 0; i < Nr; i++)
			p[i] = new double[Nc];
	};

	~matrix()
	{
		delete_all();
	}
	double* operator[](int i) { return p[i]; };

	double& get( int i, int j ) const { return p[i][j]; }
	int getRow() const { return Nr; }
	int getCol() const { return Nc; }

	void zero()
	{
		for (int i = 0; i < Nr; i++) 
			for (int j = 0; j < Nc; j++) 
				p[i][j] = 0;
	}
	void copy(matrix& b)
	{
		init(b.Nr, b.Nc);
		for (int i = 0; i < Nr; i++) 
			for (int j = 0; j < Nc; j++) 
				p[i][j] = b.p[i][j];
	}
};


#endif