# Behavioral Modeling & Software Architecture: MAKEUP Recommendation Engine

Architectural and behavioral modeling documentation for the **MAKEUP** e-commerce recommendation system using standard UML diagrams (**Activity**, **Sequence**, **Component**, and **Deployment**).

---

## 1. Activity Diagram — Recommended Product Purchase Flow

Visualizes the end-to-end workflow for discovering and purchasing a recommended product, grouped by swimlanes (**User**, **Frontend**, **Backend**)[cite: 31]:

1. **User** opens a product page[cite: 31].
2. **Frontend** (`makeup.com.ua`) sends an asynchronous AJAX request for recommendations[cite: 31].
3. **Backend** queries the ML service (`RecsService`), retrieves product metadata (price, images) from the database, and returns the payload[cite: 31].
4. **Frontend** renders the recommendation widget[cite: 31].
5. **Decision Gate (`[Interested in recommendation?]`):**
   * **No:** Flow terminates[cite: 31].
   * **Yes:** User clicks the recommended item, triggering parallel backend processing (fork): processing the order (payment & delivery) and emitting a purchase event to retrain the ML model[cite: 31].

<img width="1193" height="592" alt="image" src="https://github.com/user-attachments/assets/37ec233c-a7fa-49ce-910c-dfb3549ed6e5" />
---

## 2. Sequence Diagram — Recommendation Retrieval Lifecycle

Models time-ordered message exchanges across system components when loading recommendations[cite: 31, 32]:

1. **User** $\rightarrow$ **Interface (`makeup.com.ua`)**: Opens product page[cite: 32].
2. **Interface** $\rightarrow$ **Backend (API)**: Requests recommendations[cite: 32].
3. **Backend (API)** $\rightarrow$ **ML Service**: Requests generated product IDs[cite: 32].
4. **ML Service** $\rightarrow$ **Backend (API)**: Returns list of recommended IDs[cite: 32].
5. **ML Service** $\leftrightarrow$ **Product Database**: Queries and retrieves product details (photos, prices)[cite: 32].
6. **Backend (API)** $\rightarrow$ **Interface**: Returns formatted JSON payload with recommendations[cite: 32].
7. **Interface** $\rightarrow$ **User**: Renders final results[cite: 32].

<img width="972" height="561" alt="image" src="https://github.com/user-attachments/assets/c2530853-654e-47e4-b746-20d6652ce3d5" />
---

## 3. Component Diagram — Logical Software Architecture

Defines the modular structure and dependencies of the platform[cite: 32]:

* **`<<UI>>` MakeupSite (Frontend):** Communicates with the backend via REST API (`<<uses REST API>>`)[cite: 32].
* **`<<component>>` APIGateway (Backend):** Central routing and business logic layer interacting with databases (`<<uses>>`) and the recommendation service (`<<uses Recs API>>`)[cite: 32].
* **`<<service>>` RecsService (ML):** Dedicated recommendation microservice reading historical and catalog data (`<<reads>>`)[cite: 32].
* **`<<database>>` ProductDB & UserDB:** Persistent storage for product catalogs and user profiles/interactions[cite: 32].

<img width="851" height="612" alt="image" src="https://github.com/user-attachments/assets/67d71356-d529-447b-91a3-724f3c723190" />
---

## 4. Deployment Diagram — Physical Infrastructure

Illustrates the physical mapping of software artifacts across hardware nodes and network protocols[cite: 33]:

* **Client Device:** Runs `Web Browser`, communicating with the application cluster over **HTTPS**[cite: 33].
* **Web Application Servers (`makeup.com.ua` Cluster):** Hosts `APIGateway (Backend)`, connecting to internal services via **Internal API Calls** and databases over **TCP/IP**[cite: 33].
* **ML Service Cluster (Kubernetes / K8s):** Dedicated cluster hosting `RecsService` and serialized model artifacts (`MLModel.pkl`)[cite: 33].
* **Database Server:** Hosts `ProductDB` and `UserDB` instances accessible via **TCP/IP**[cite: 33].

<img width="1046" height="597" alt="image" src="https://github.com/user-attachments/assets/55c47c04-7720-4281-98c5-bab3b105ddfc" />
