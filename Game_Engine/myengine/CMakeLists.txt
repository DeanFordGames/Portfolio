cmake_minimum_required(VERSION 3.0)
project(MYENGINE)


	include_directories(
		src
		src/pellet
		contrib/windows-cl-amd64/include
	)

	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
	)

	add_library(rend
		src/rend/Animation.h
		src/rend/Animation.cpp

		src/rend/Buffer.h
		src/rend/Buffer.cpp

		src/rend/Mesh.h
		src/rend/Mesh.cpp

		src/rend/Model.h
		src/rend/Model.cpp

		src/rend/ModelRenderer.h
		src/rend/ModelRenderer.cpp

		src/rend/RenderTexture.h
		src/rend/RenderTexture.cpp

		src/rend/Renderer.h
		src/rend/Renderer.cpp

		src/rend/Shader.h
		src/rend/Shader.cpp

		src/rend/Texture.h
		src/rend/Texture.cpp

		src/rend/rendmath.h
		src/rend/rendmath.cpp
	)

	target_link_libraries(rend GLEW32 OPENGL32)

	add_library(pellet
		  src/pellet/Bullet3Collision/BroadPhaseCollision/b3DynamicBvh.cpp
		  src/pellet/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.cpp
		  src/pellet/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.cpp
		  src/pellet/Bullet3Collision/NarrowPhaseCollision/b3ConvexUtility.cpp
		  src/pellet/Bullet3Collision/NarrowPhaseCollision/b3CpuNarrowPhase.cpp
		  src/pellet/Bullet3Common/b3AlignedAllocator.cpp
		  src/pellet/Bullet3Common/b3Logging.cpp
		  src/pellet/Bullet3Common/b3Vector3.cpp
		  src/pellet/Bullet3Dynamics/b3CpuRigidBodyPipeline.cpp
		  src/pellet/Bullet3Dynamics/ConstraintSolver/b3FixedConstraint.cpp
		  src/pellet/Bullet3Dynamics/ConstraintSolver/b3Generic6DofConstraint.cpp
		  src/pellet/Bullet3Dynamics/ConstraintSolver/b3PgsJacobiSolver.cpp
		  src/pellet/Bullet3Dynamics/ConstraintSolver/b3Point2PointConstraint.cpp
		  src/pellet/Bullet3Dynamics/ConstraintSolver/b3TypedConstraint.cpp
		  src/pellet/Bullet3Geometry/b3ConvexHullComputer.cpp
		  src/pellet/Bullet3Geometry/b3GeometryUtil.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btDbvt.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btDispatcher.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp
		  src/pellet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCollisionObject.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCollisionWorld.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCollisionWorldImporter.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btCompoundCompoundCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btGhostObject.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btHashedSimplePairCache.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btManifoldResult.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/CollisionDispatch/btUnionFind.cpp
		  src/pellet/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp
		  src/pellet/BulletCollision/CollisionShapes/btBox2dShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btBoxShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btCapsuleShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btCollisionShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btCompoundShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConcaveShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConeShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvex2dShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexHullShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexInternalShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btCylinderShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btEmptyShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btMultiSphereShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btOptimizedBvh.cpp
		  src/pellet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btShapeHull.cpp
		  src/pellet/BulletCollision/CollisionShapes/btSphereShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTetrahedronShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleBuffer.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleCallback.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleMesh.cpp
		  src/pellet/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp
		  src/pellet/BulletCollision/CollisionShapes/btUniformScalingShape.cpp
		  src/pellet/BulletCollision/Gimpact/btContactProcessing.cpp
		  src/pellet/BulletCollision/Gimpact/btGenericPoolAllocator.cpp
		  src/pellet/BulletCollision/Gimpact/btGImpactBvh.cpp
		  src/pellet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp
		  src/pellet/BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp
		  src/pellet/BulletCollision/Gimpact/btGImpactShape.cpp
		  src/pellet/BulletCollision/Gimpact/btTriangleShapeEx.cpp
		  src/pellet/BulletCollision/Gimpact/gim_box_set.cpp
		  src/pellet/BulletCollision/Gimpact/gim_contact.cpp
		  src/pellet/BulletCollision/Gimpact/gim_memory.cpp
		  src/pellet/BulletCollision/Gimpact/gim_tri_collision.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp
		  src/pellet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp
		  src/pellet/BulletDynamics/Character/btKinematicCharacterController.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btContactConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btFixedConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btGearConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp
		  src/pellet/BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp
		  src/pellet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp
		  src/pellet/BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.cpp
		  src/pellet/BulletDynamics/Dynamics/btRigidBody.cpp
		  src/pellet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp
		  src/pellet/BulletDynamics/Dynamics/btSimulationIslandManagerMt.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBody.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyConstraint.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyConstraintSolver.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyFixedConstraint.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyJointMotor.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodyPoint2Point.cpp
		  src/pellet/BulletDynamics/Featherstone/btMultiBodySliderConstraint.cpp
		  src/pellet/BulletDynamics/MLCPSolvers/btDantzigLCP.cpp
		  src/pellet/BulletDynamics/MLCPSolvers/btLemkeAlgorithm.cpp
		  src/pellet/BulletDynamics/MLCPSolvers/btMLCPSolver.cpp
		  src/pellet/BulletDynamics/Vehicle/btRaycastVehicle.cpp
		  src/pellet/BulletDynamics/Vehicle/btWheelInfo.cpp
		  src/pellet/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp
		  src/pellet/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp
		  src/pellet/BulletInverseDynamics/IDMath.cpp
		  src/pellet/BulletInverseDynamics/MultiBodyTree.cpp
		  src/pellet/BulletSoftBody/btDefaultSoftBodySolver.cpp
		  src/pellet/BulletSoftBody/btSoftBody.cpp
		  src/pellet/BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.cpp
		  src/pellet/BulletSoftBody/btSoftBodyHelpers.cpp
		  src/pellet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.cpp
		  src/pellet/BulletSoftBody/btSoftMultiBodyDynamicsWorld.cpp
		  src/pellet/BulletSoftBody/btSoftRigidCollisionAlgorithm.cpp
		  src/pellet/BulletSoftBody/btSoftRigidDynamicsWorld.cpp
		  src/pellet/BulletSoftBody/btSoftSoftCollisionAlgorithm.cpp
		  src/pellet/LinearMath/btAlignedAllocator.cpp
		  src/pellet/LinearMath/btConvexHull.cpp
		  src/pellet/LinearMath/btConvexHullComputer.cpp
		  src/pellet/LinearMath/btGeometryUtil.cpp
		  src/pellet/LinearMath/btPolarDecomposition.cpp
		  src/pellet/LinearMath/btQuickprof.cpp
		  src/pellet/LinearMath/btSerializer.cpp
		  src/pellet/LinearMath/btThreads.cpp
		  src/pellet/LinearMath/btVector3.cpp
	)

	add_library(myengine
		src/myengine/myengine.h

		src/myengine/Core.h
		src/myengine/Core.cpp

		src/myengine/Entity.h
		src/myengine/Entity.cpp

		src/myengine/Component.h
		src/myengine/Component.cpp

		src/myengine/TriangleRenderer.h
		src/myengine/TriangleRenderer.cpp

		src/myengine/Transform.h
		src/myengine/Transform.cpp

		src/myengine/Keyboard.h
		src/myengine/Keyboard.cpp

		src/myengine/Enviroment.h
		src/myengine/Enviroment.cpp

		src/myengine/SoundSource.h
		src/myengine/SoundSource.cpp

		src/myengine/Resource.h
		src/myengine/Resource.cpp

		src/myengine/Resources.h
		src/myengine/Resources.cpp

		src/myengine/BoxCollider.h
		src/myengine/BoxCollider.cpp

		src/myengine/RigidBody.h
		src/myengine/RigidBody.cpp

		src/myengine/IrcComponent.h
		src/myengine/IrcComponent.cpp

		src/myengine/Audio.h
		src/myengine/Audio.cpp

		src/myengine/Texture.h
		src/myengine/Texture.cpp

		src/myengine/ModelRenderer.h
		src/myengine/ModelRenderer.cpp

		src/myengine/Model.h
		src/myengine/Model.cpp

		src/myengine/Physics.h
		src/myengine/Physics.cpp

		src/myengine/Camera.h
		src/myengine/Camera.cpp
	)

	target_link_libraries(myengine rend pellet SDL2)

	target_link_libraries(myengine SDL2 SDL2main openal32 ws2_32)


add_executable(game
	src/game/main.cpp

	src/game/Player.h
	src/game/Player.cpp

	src/game/Handler.h
	src/game/Handler.cpp

	src/game/Enemy.h
	src/game/Enemy.cpp
)

target_link_libraries(game myengine)