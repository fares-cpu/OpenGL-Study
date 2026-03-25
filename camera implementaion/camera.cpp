#include<iostream>

struct vec4 {
	float values[4];

	vec4() {
		for (int i = 0; i < 4; i++)
			values[i] = 0;
	}
	vec4(float x, float y, float z, float w) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
	}
	const float& operator[](int index) const{
		return values[index];
	}
	float& operator[](int index){
		return values[index];
	}

	const vec4& operator*(vec4& v) const{
		return vec4(
			values[0] * v[0],
			values[1] * v[1],
			values[2] * v[2],
			values[3] * v[3]
		);
	}
	const vec4& operator*(vec4& v) {
		return vec4(
			values[0] * v[0],
			values[1] * v[1],
			values[2] * v[2],
			values[3] * v[3]
		);
	}

};

struct mat4 {
	vec4 columns[4];

	mat4() {
		columns[0] = vec4(1, 0, 0, 0);
		columns[1] = vec4(0, 1, 0, 0);
		columns[2] = vec4(0, 0, 1, 0);
		columns[3] = vec4(0, 0, 0, 1);
	}
	mat4(vec4 x, vec4 y, vec4 z, vec4 w) {
		columns[0] = x;
		columns[1] = y;
		columns[2] = z;
		columns[3] = w;
	}

	const vec4& operator[](int index) const{
		return columns[index];
	}
	vec4& operator[](int index) {
		return columns[index];
	}
	const vec4& operator* (vec4& v){
		return vec4(
			columns[0][0] * v[0] + columns[1][0] * v[1] + columns[2][0] * v[2] + columns[3][0] * v[3],
			columns[0][1] * v[0] + columns[1][1] * v[1] + columns[2][1] * v[2] + columns[3][1] * v[3],
			columns[0][2] * v[0] + columns[1][2] * v[1] + columns[2][2] * v[2] + columns[3][2] * v[3],
			columns[0][3] * v[0] + columns[1][3] * v[1] + columns[2][3] * v[2] + columns[3][3] * v[3]
		);
	}
	const mat4& operator* (mat4& m){
		return mat4(
			*this * m[0],
			*this * m[1],
			*this * m[2],
			*this * m[3]
		);
	}
};


