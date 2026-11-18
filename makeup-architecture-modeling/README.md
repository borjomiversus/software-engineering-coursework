# Behavioral Modeling & Software Architecture: MAKEUP Recommendation Engine

Architectural and behavioral modeling documentation for the **MAKEUP** e-commerce recommendation system using standard UML diagrams (**Activity**, **Sequence**, **Component**, and **Deployment**).

---

## 1. Activity Diagram — Recommended Product Purchase Flow

Visualizes the end-to-end workflow for discovering and purchasing a recommended product, grouped by swimlanes (**User**, **Frontend**, **Backend**):

1. **User** opens a product page.
2. **Frontend** (`makeup.com.ua`) sends an asynchronous AJAX request for recommendations.
3. **Backend** queries the ML service (`RecsService`), retrieves product metadata (price, images) from the database, and returns the payload.
4. **Frontend** renders the recommendation widget.
5. **Decision Gate (`[Interested in recommendation?]`):**
   * **No:** Flow terminates.
   * **Yes:** User clicks the recommended item, triggering parallel backend processing (fork): processing the order (payment & delivery) and emitting a purchase event to retrain the ML model.

<img width="1193" height="592" alt="Activity Diagram" src="https://github.com/user-attachments/assets/37ec233c-a7fa-49ce-910c-dfb3549ed6e5" />

---

## 2. Sequence Diagram — Recommendation Retrieval Lifecycle

Models time-ordered message exchanges across system components when loading recommendations:

1. **User** $\rightarrow$ **Interface (`makeup.com.ua`)**: Opens product page.
2. **Interface** $\rightarrow$ **Backend (API)**: Requests recommendations.
3. **Backend (API)** $\rightarrow$ **ML Service**: Requests generated product IDs.
4. **ML Service** $\rightarrow$ **Backend (API)**: Returns list of recommended IDs.
5. **ML Service** $\leftrightarrow$ **Product Database**: Queries and retrieves product details (photos, prices).
6. **Backend (API)** $\rightarrow$ **Interface**: Returns formatted JSON payload with recommendations.
7. **Interface** $\rightarrow$ **User**: Renders final results.

<img width="972" height="561" alt="Sequence Diagram" src="https://github.com/user-attachments/assets/c2530853-654e-47e4-b746-20d6652ce3d5" />

---

## 3. Component Diagram — Logical Software Architecture

Defines the modular structure and dependencies of the platform:

* **`<<UI>>` MakeupSite (Frontend):** Communicates with the backend via REST API (`<<uses REST API>>`).
* **`<<component>>` APIGateway (Backend):** Central routing and business logic layer interacting with databases (`<<uses>>`) and the recommendation service (`<<uses Recs API>>`).
* **`<<service>>` RecsService (ML):** Dedicated recommendation microservice reading historical and catalog data (`<<reads>>`).
* **`<<database>>` ProductDB & UserDB:** Persistent storage for product catalogs and user profiles/interactions.

<img width="851" height="612" alt="Component Diagram" src="https://github.com/user-attachments/assets/67d71356-d529-447b-91a3-724f3c723190" />

---

## 4. Deployment Diagram — Physical Infrastructure

Illustrates the physical mapping of software artifacts across hardware nodes and network protocols:

* **Client Device:** Runs `Web Browser`, communicating with the application cluster over **HTTPS**.
* **Web Application Servers (`makeup.com.ua` Cluster):** Hosts `APIGateway (Backend)`, connecting to internal services via **Internal API Calls** and databases over **TCP/IP**.
* **ML Service Cluster (Kubernetes / K8s):** Dedicated cluster hosting `RecsService` and serialized model artifacts (`MLModel.pkl`).
* **Database Server:** Hosts `ProductDB` and `UserDB` instances accessible via **TCP/IP**.

<img width="1046" height="597" alt="Deployment Diagram" src="https://github.com/user-attachments/assets/55c47c04-7720-4281-98c5-bab3b105ddfc" />
