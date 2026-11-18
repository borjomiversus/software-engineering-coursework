# Requirements Engineering & Use Case Analysis: MAKEUP E-Commerce Platform

System analysis documentation for the **MAKEUP** online cosmetics and personal care platform, covering Product Vision, Business/User/Functional/Non-Functional Requirements, and a detailed Use Case specification.

---

## 1. Product Vision

* **For:** Men and women who want to buy cosmetics, perfumes, and personal care products quickly, conveniently, and profitably.
* **Who value:** Wide product assortment, quality customer service, and authentic international brands.
* **MAKEUP** is an e-commerce platform offering nationwide delivery across Ukraine, personalized product recommendations, verified customer reviews, and access to promotional deals.
* **Unlike** online stores with limited catalogs or complex delivery terms, **MAKEUP** combines an intuitive interface, fast shipping, competitive pricing, and verified brand authenticity.

---

## 2. Requirements Specification

### Business Requirements
* Increase sales of cosmetics, perfumes, and personal care items through targeted advertising.
* Provide customers with guaranteed access to original products from international brands.
* Improve customer loyalty and retention via fast delivery and convenient service.
* Expand market share in the Ukrainian beauty e-commerce segment.
* Ensure a simple and secure checkout process for every user.

### User Requirements
* As a shopper, I want to quickly find the right product by category to save time.
* As a registered user, I want to save items to "Favorites" to easily return to them later.
* As a visitor, I want to read reviews from other buyers to make informed purchasing decisions.
* As a shopper, I want to track my order status online to know when to expect delivery.
* As a user, I want to receive personalized recommendations to discover relevant items faster.

### Functional Requirements (User Stories)

| User Story | System Implementation |
| :--- | :--- |
| As a shopper, I want to search products by category, brand, and price to quickly find what I need. | Search engine with multi-criteria filtering (price, brand, category, rating). |
| As a registered user, I want to add items to "Favorites" to revisit them later. | "Add to Favorites" button on product pages synced with the user profile. |
| As a visitor, I want to view customer reviews to make a balanced purchase decision. | "Reviews" block featuring a 1–5 star rating system and text comments. |
| As a registered user, I want to track my order to know its current status. | Order tracking dashboard displaying statuses (*Processing*, *Shipped*, *Delivered*). |
| As a shopper, I want to add items to a cart to place an order. | "Add to Cart" button with dynamic cart badge counter updates. |
| As a system administrator, I want to edit the product catalog to keep inventory up to date. | Admin panel CRUD functionality for adding, editing, and removing products. |
| As a shopper, I want to receive personal recommendations tailored to my preferences. | Recommendation block generated from browsing and purchase history. |
| As a shopper, I want to pay online to complete my purchase quickly. | Payment gateway integration supporting bank cards, Google Pay, and Apple Pay. |
| As a visitor, I want to switch the website language for comfortable navigation. | Default Ukrainian localization with manual language switcher. |
| As a shopper, I want to see promotional offers to buy at a discount. | Dedicated "Promotions & Deals" section featuring discounted products. |

### Non-Functional Requirements
* **Performance:** Product search must render results in $\le 3\text{ seconds}$ under a load of 500 users/min.
* **Scalability:** System must support up to 50,000 concurrent users.
* **Security:** All transactions must be encrypted via HTTPS; passwords must be stored in hashed form.
* **Availability:** 99.9% monthly uptime (UTC+3).
* **Usability:** Responsive, mobile-friendly user interface.

---

## 3. Use Case Specification: "Add Product to Cart"
<img width="1225" height="457" alt="image" src="https://github.com/user-attachments/assets/67ae89d6-7c59-4c60-adf5-88240ac89cb1" />

* **Short Description:** User adds a product to the shopping cart to proceed with an order. The system verifies stock availability, updates the cart state, and confirms the action.
* **Actor:** Shopper (Registered or Guest user).
* **Preconditions:**
  * System is operational.
  * User is on the selected product page.
  * Product is in stock and available for purchase.

### Basic Flow
1. User clicks the **"Add to Cart"** button on the product page.
   * *1.1.* If the product is in stock $\rightarrow$ item is added to the cart.
   * *1.2.* If the product is out of stock $\rightarrow$ transition to **Alternative Flow A1**.
2. System displays a confirmation notification:
   * *2.1.* Cart icon counter in the top-right corner updates with the new item count.
   * *2.2.* A modal popup appears with **"Continue Shopping"** and **"Proceed to Checkout"** buttons.
3. User navigates to the cart to complete the order or continues browsing.

### Alternative Flows
* **A1. Out of Stock:** System displays *"Product temporarily unavailable"* and prevents adding the item to the cart.
* **A2. Server Error:** If the server fails to update cart data, system displays *"Error adding item. Please try again later."*
* **A3. Invalid Session:** If the user's session has expired, system prompts re-authentication before continuing.

### UML Use Case Diagram
<img width="1062" height="667" alt="image" src="https://github.com/user-attachments/assets/fe200737-8aef-4a13-8ecf-9ea84d02f97d" />
