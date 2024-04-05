#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 150; i++) {

		auto deg = ofRandom(360);
		auto location = glm::vec2(200 * cos(deg * DEG_TO_RAD), 200 * sin(deg * DEG_TO_RAD));
		auto next = glm::vec2(201 * cos(deg * DEG_TO_RAD), 201 * sin(deg * DEG_TO_RAD));

		vector<glm::vec2> log;
		log.push_back(location);

		this->log_list.push_back(log);
		if (ofRandom(100) < 50) {

			this->velocity_list.push_back(next - location);
		}
		else {

			this->velocity_list.push_back(location - next);
		}
		this->speed_list.push_back(ofRandom(5, 10));
		this->life_list.push_back(15);

		this->color_list.push_back(ofColor(100));
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		auto fueture = glm::normalize(this->velocity_list[i]) * 30;
		auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.01, ofGetFrameNum() * 0.005)), 0, 1, -360, 360);
		fueture = fueture + glm::vec2(10 * cos(deg * DEG_TO_RAD), 10 * sin(deg * DEG_TO_RAD));
		fueture = this->log_list[i].back() + glm::normalize(fueture) * this->speed_list[i];
		this->log_list[i].push_back(fueture);

		this->life_list[i] -= 1;

		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(this->color_list[i], ofMap(this->life_list[i], 0, 15, 32, 255));
		
		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}