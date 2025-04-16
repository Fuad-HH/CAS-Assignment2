#include "CalculateStiffnessMatrixAndLoadVector.hpp" 


Results calculateAllElementStiffnessMatrixAndLoadVector(const Mesh& mesh, double k) {

    int numElements = mesh.GetNumElements();
	    
	int numNodes = mesh.GetNumNodesPerElement();

    int sizePerElement = numNodes * numNodes; 
	View1D allElementStiffnessMatrix("stores all element stiffness matrix", numElements * sizePerElement);
	View1D allElementLoadVector("stores all element load vector", numElements * numNodes);
    
	Kokkos::parallel_for("CalculateStiffness", numElements,
        KOKKOS_LAMBDA(const int elemIdx) {

		if (numNodes == 3) { // Triangle element
                TriElement triElem(mesh, elemIdx);
                triElem.setMaterialProperty(k);
				double stiffnessMatrixPerElement[MAX_STIFFNESS_MATRIX_SIZE] = {};
				double loadVectorPerElement[MAX_LOAD_VECTOR_SIZE] = {};
                triElem.computeElementStiffnessMatrix(stiffnessMatrixPerElement);
				triElem.computeElementLoadVector(loadVectorPerElement);
        } else { // Quad element
                QuadElement quadElem(mesh, elemIdx);
                quadElem.setMaterialProperty(k);
				double stiffnessMatrixPerElement[MAX_STIFFNESS_MATRIX_SIZE] = {};
				double loadVectorPerElement[MAX_LOAD_VECTOR_SIZE] = {};
                quadElem.computeElementStiffnessMatrix(stiffnessMatrixPerElement);
				quadElem.computeElementLoadVector(loadVectorPerElement);
        }
			
		int base_stiffness_idx = elemIdx * sizePerElement;
		for (int i = 0; i < sizePerElement; ++i){
			allElementStiffnessMatrix(base_stiffness_idx + i) = stiffnessMatrixPerElement[i]; 	
		}
		
		int base_load_idx = elemIdx * numNodes; 

		for (int i = 0; i < numNodes; ++i){
			allElementLoadVector(base_load_idx + i) = loadVectorPerElement[i];	
		}

        });

	Results{allElementStiffnessMatrix, allElementLoadVector};
}
