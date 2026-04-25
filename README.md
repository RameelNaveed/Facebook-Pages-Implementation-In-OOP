# Social Network Simulation (C++)

A comprehensive Object-Oriented Programming (OOP) project that simulates a functional social network environment. The system allows users to interact with friends, follow pages, post content, like/comment on posts, and manage "memories" of past activities.

## 🚀 Features

- **User Management**: Load and manage user profiles, friend lists, and page subscriptions.
- **Social Interactions**:
    - **Likes**: Users can like posts from friends or pages.
    - **Comments**: Interactive commenting system for posts.
    - **Friend Lists**: View and manage connections between users.
- **Content System**:
    - **Posts**: Supports text-based posts from both users and pages.
    - **Activities**: Posts can include specific activities (e.g., "Feeling excited", "Celebrating").
    - **Timeline**: View a chronological feed of a user's own posts.
    - **Home Feed**: A curated view of recent posts from friends and followed pages.
- **Memory System**: A unique feature that allows users to "look back" at posts from previous years and re-share them on their timeline.
- **Object-Oriented Design**: Built using core OOP principles including Inheritance, Polymorphism (for Users and Pages), and Composition.

## 🛠️ Built With

- **Language**: C++
- **Build System**: Visual Studio 2022 (.sln / .vcxproj)
- **Data Storage**: Flat-file database system (.txt files)

## 📁 Project Structure

- `23L-0683_Project.cpp`: The main source code containing all class definitions and logic.
- `SocialNetworkUsers.txt`: Database of user profiles.
- `SocialNetworkPages.txt`: Database of pages available in the network.
- `SocialNetworkPosts.txt`: Historical record of all posts.
- `SocialNetworkComments.txt`: Data for comments linked to specific posts.
- `SocialNetworkActivities.txt`: Pre-defined activities for posts.
- `UserFriendsandLikedPages.txt`: Relationships between users and pages.

---
*This project was developed as part of an Object-Oriented Programming course.*
