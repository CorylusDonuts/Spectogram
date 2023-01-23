#pragma once


class Shader {
private:
	unsigned int ID;
	unsigned int Compile(unsigned int type, const char* source);
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void setUint(const char* name, unsigned int& value);
	void setInt(const char* name, int& value);
	
	void set4F(const char* name, float& val1, float& val2, float& val3, float& val4);
	void set3F(const char* name, float& val1, float& val2, float& val3);
	void set2F(const char* name, float& val1, float& val2);
	void set1F(const char* name, float& val1);

	void set4D(const char* name, double& val1, double& val2, double& val3, double& val4);
	void set3D(const char* name, double& val1, double& val2, double& val3);
	void set2D(const char* name, double& val1, double& val2);
	void set1D(const char* name, double& val1);

	void Bind();
	void Unbind();
	void Delete();
};