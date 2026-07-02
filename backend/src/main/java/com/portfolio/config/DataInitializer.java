package com.portfolio.config;

import com.portfolio.model.Project;
import com.portfolio.model.Expertise;
import com.portfolio.repository.ProjectRepository;
import com.portfolio.repository.ExpertiseRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.Arrays;

@Component
public class DataInitializer implements CommandLineRunner {

    @Autowired
    private ProjectRepository projectRepository;

    @Autowired
    private ExpertiseRepository expertiseRepository;

    @Override
    public void run(String... args) throws Exception {
        // Initialize Projects
        initializeProjects();
        // Initialize Expertise
        initializeExpertise();
    }

    private void initializeProjects() {
        Project p1 = new Project();
        p1.setTitle("AD Forest Consolidation");
        p1.setDescription("Successfully migrated 50,000+ users across 3 domains into unified forest with zero downtime. Implemented trust relationships and security policies");
        p1.setGradient("gradient-1");
        p1.setTags(Arrays.asList("Active Directory", "Migration", "Security"));
        p1.setProjectType("Active Directory");
        p1.setUsersImpacted(50000);
        p1.setDuration("6 months");
        projectRepository.save(p1);

        Project p2 = new Project();
        p2.setTitle("Citrix XenDesktop Deployment");
        p2.setDescription("Architected and deployed VDI environment supporting 10,000 concurrent users with 99.99% uptime SLA");
        p2.setGradient("gradient-2");
        p2.setTags(Arrays.asList("Citrix", "VDI", "Infrastructure"));
        p2.setProjectType("Citrix");
        p2.setUsersImpacted(10000);
        p2.setDuration("8 months");
        projectRepository.save(p2);

        Project p3 = new Project();
        p3.setTitle("Exchange 2016 to 2019 Migration");
        p3.setDescription("Planned and executed enterprise-wide Exchange migration for 30,000 mailboxes with zero data loss");
        p3.setGradient("gradient-3");
        p3.setTags(Arrays.asList("Exchange", "Migration", "Email"));
        p3.setProjectType("Exchange");
        p3.setUsersImpacted(30000);
        p3.setDuration("4 months");
        projectRepository.save(p3);

        Project p4 = new Project();
        p4.setTitle("Hybrid Identity Solution");
        p4.setDescription("Implemented Entra ID Connect with MFA, conditional access policies, and seamless cloud integration");
        p4.setGradient("gradient-4");
        p4.setTags(Arrays.asList("Entra ID", "Azure", "Hybrid"));
        p4.setProjectType("Entra ID");
        p4.setUsersImpacted(25000);
        p4.setDuration("3 months");
        projectRepository.save(p4);

        Project p5 = new Project();
        p5.setTitle("BeyondTrust PAM Implementation");
        p5.setDescription("Deployed privileged access management system with session recording and compliance audit trails");
        p5.setGradient("gradient-5");
        p5.setTags(Arrays.asList("Security", "PAM", "Compliance"));
        p5.setProjectType("Security");
        p5.setUsersImpacted(5000);
        p5.setDuration("5 months");
        projectRepository.save(p5);

        Project p6 = new Project();
        p6.setTitle("Disaster Recovery Setup");
        p6.setDescription("Built comprehensive DR solution for critical infrastructure with automated failover and RPO < 1 hour");
        p6.setGradient("gradient-6");
        p6.setTags(Arrays.asList("DR/BC", "Automation", "Backup"));
        p6.setProjectType("Infrastructure");
        p6.setUsersImpacted(100000);
        p6.setDuration("7 months");
        projectRepository.save(p6);
    }

    private void initializeExpertise() {
        Expertise e1 = new Expertise();
        e1.setTitle("Active Directory");
        e1.setDescription("Domain architecture, GPO management, user provisioning, security hardening, and hybrid cloud integration");
        e1.setIcon("fas fa-key");
        e1.setCardColor("card-blue");
        expertiseRepository.save(e1);

        Expertise e2 = new Expertise();
        e2.setTitle("Citrix & VDI");
        e2.setDescription("Virtual desktop infrastructure, Citrix XenDesktop, workspace management, and performance optimization");
        e2.setIcon("fas fa-window-restore");
        e2.setCardColor("card-purple");
        expertiseRepository.save(e2);

        Expertise e3 = new Expertise();
        e3.setTitle("Exchange Server");
        e3.setDescription("Email administration, mailbox management, disaster recovery, migration planning, and hybrid deployment");
        e3.setIcon("fas fa-envelope");
        e3.setCardColor("card-teal");
        expertiseRepository.save(e3);

        Expertise e4 = new Expertise();
        e4.setTitle("Entra ID & Azure");
        e4.setDescription("Cloud identity management, conditional access, hybrid sync, and Azure resource administration");
        e4.setIcon("fas fa-cloud");
        e4.setCardColor("card-coral");
        expertiseRepository.save(e4);

        Expertise e5 = new Expertise();
        e5.setTitle("Remote Access");
        e5.setDescription("Bomgar/BeyondTrust implementation, VPN solutions, and secure remote support infrastructure");
        e5.setIcon("fas fa-tools");
        e5.setCardColor("card-green");
        expertiseRepository.save(e5);

        Expertise e6 = new Expertise();
        e6.setTitle("Systems Architecture");
        e6.setDescription("Infrastructure design, capacity planning, redundancy, and business continuity solutions");
        e6.setIcon("fas fa-network-wired");
        e6.setCardColor("card-orange");
        expertiseRepository.save(e6);
    }
}
