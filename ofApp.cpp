#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	int len = 500;
	int depth = 50;
	int base_radius = 200;

	for (int z = -250; z <= 250; z += 125) {

		for (int param = 0; param < 100; param++) {

			auto face_index = this->face.getNumVertices();
			auto frame_index = this->frame.getNumVertices();

			auto deg = param * 3.6 - 135;
			auto next_deg = (param + 1) * 3.6 - 135;

			int radius = ofMap(ofNoise(glm::vec4(base_radius * cos(deg * DEG_TO_RAD) * 0.005, base_radius * sin(deg * DEG_TO_RAD) * 0.005, z * 0.01, ofGetFrameNum() * 0.02)), 0, 1, base_radius - 30, base_radius + 30);
			int next_radius = ofMap(ofNoise(glm::vec4(base_radius * cos(next_deg * DEG_TO_RAD) * 0.005, base_radius * sin(next_deg * DEG_TO_RAD) * 0.005, z * 0.01, ofGetFrameNum() * 0.02)), 0, 1, base_radius - 30, base_radius + 30);

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z - depth * 0.5));
			vertices.push_back(glm::vec3(this->make_point(len, param), z - depth * 0.5));
			vertices.push_back(glm::vec3(this->make_point(len, param + 1), z - depth * 0.5));
			vertices.push_back(glm::vec3(next_radius * cos(next_deg * DEG_TO_RAD), next_radius * sin(next_deg * DEG_TO_RAD), z - depth * 0.5));

			vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z + depth * 0.5));
			vertices.push_back(glm::vec3(this->make_point(len, param), z + depth * 0.5));
			vertices.push_back(glm::vec3(this->make_point(len, param + 1), z + depth * 0.5));
			vertices.push_back(glm::vec3(next_radius * cos(next_deg * DEG_TO_RAD), next_radius * sin(next_deg * DEG_TO_RAD), z + depth * 0.5));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);

			this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 6);
			this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 7);

			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 7);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 7); this->face.addIndex(face_index + 4);

			this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 6);
			this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 2);

			this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 3);
			this->frame.addIndex(frame_index + 4); this->frame.addIndex(frame_index + 7);

			this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 2);
			this->frame.addIndex(frame_index + 5); this->frame.addIndex(frame_index + 6);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}