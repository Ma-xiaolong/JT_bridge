#pragma once
#include <memory>
class DtExerciseConn;

// 自定义删除器，用于删除 DtExerciseConn
// 这样可以在头文件中使用前向声明，而不需要完整定义
struct DtExerciseConnDeleter {
	void operator()(DtExerciseConn* p) const;
};

class VRLinkManager {
public:
	static VRLinkManager& I();
	bool init(const char* federation, const char* federate);
	void pumpOnce();   // drainInput + tickAll
	void shutdown();

	DtExerciseConn* conn() const { return _conn.get(); }

	bool publishRadarControlInteraction(const char* platform_id,
		const char* equipment_id,
		int state,
		double mission_time);

	// 析构函数需要在实现文件中定义，以便正确删除 DtExerciseConn
	~VRLinkManager();

private:
	VRLinkManager() {}
	std::unique_ptr<DtExerciseConn, DtExerciseConnDeleter> _conn;
};
