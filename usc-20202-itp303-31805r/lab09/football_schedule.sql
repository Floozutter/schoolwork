-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Oct 21, 2019 at 09:26 PM
-- Server version: 10.1.41-MariaDB
-- PHP Version: 7.2.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

-- --------------------------------------------------------

--
-- Table structure for table `days`
--

CREATE TABLE `days` (
  `id` int(11) NOT NULL,
  `day` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `days`
--

INSERT INTO `days` (`id`, `day`) VALUES
(1, 'Sun'),
(2, 'Mon'),
(3, 'Tue'),
(4, 'Wed'),
(5, 'Thu'),
(6, 'Fri'),
(7, 'Sat');

-- --------------------------------------------------------

--
-- Table structure for table `schedule`
--

CREATE TABLE `schedule` (
  `id` int(11) NOT NULL,
  `date` date DEFAULT NULL,
  `day_id` int(11) NOT NULL,
  `venue_id` int(11) NOT NULL,
  `away_team_id` int(11) NOT NULL,
  `home_team_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `schedule`
--

INSERT INTO `schedule` (`id`, `date`, `day_id`, `venue_id`, `away_team_id`, `home_team_id`) VALUES
(1, '2017-09-09', 7, 1, 2, 1),
(2, '2017-09-23', 7, 2, 1, 3),
(3, '2017-09-23', 7, 3, 4, 2),
(4, '2017-09-29', 6, 4, 5, 1),
(5, '2017-09-30', 7, 3, 6, 2),
(6, '2017-09-30', 7, 5, 10, 4),
(7, '2017-09-30', 7, 6, 3, 7),
(8, '2017-10-07', 7, 1, 9, 1),
(9, '2017-10-07', 7, 7, 2, 7),
(10, '2017-10-13', 6, 2, 5, 3),
(11, '2017-10-14', 7, 1, 7, 1),
(12, '2017-10-14', 7, 3, 7, 2),
(13, '2017-10-21', 7, 5, 7, 4),
(14, '2017-10-26', 5, 8, 2, 9),
(15, '2017-10-28', 7, 9, 1, 6),
(16, '2017-10-28', 7, 2, 10, 3),
(17, '2017-11-04', 6, 7, 4, 7),
(18, '2017-11-04', 6, 2, 9, 3),
(19, '2017-11-18', 7, 1, 4, 1);

-- --------------------------------------------------------

--
-- Table structure for table `teams`
--

CREATE TABLE `teams` (
  `id` int(11) NOT NULL,
  `team` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `teams`
--

INSERT INTO `teams` (`id`, `team`) VALUES
(1, 'USC Trojans'),
(2, 'Stanford Cardinal'),
(3, 'California Golden Bears'),
(4, 'UCLA Bruins'),
(5, 'Washington State Cougars'),
(6, 'Arizona State Sun Devils'),
(7, 'Oregon Ducks'),
(8, 'Utah Utes'),
(9, 'Oregon State Beavers'),
(10, 'Colorado Buffaloes');

-- --------------------------------------------------------

--
-- Table structure for table `venues`
--

CREATE TABLE `venues` (
  `id` int(11) NOT NULL,
  `venue` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `venues`
--

INSERT INTO `venues` (`id`, `venue`) VALUES
(1, 'LA Memorial Coliseum'),
(2, 'California Memorial Stadium'),
(3, 'Stanford Stadium'),
(4, 'Martin Stadium'),
(5, 'Rose Bowl'),
(6, 'Autzen Stadium'),
(7, 'Rice-Eccles Stadium'),
(8, 'Reser Stadium'),
(9, 'Sun Devil Stadium');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `days`
--
ALTER TABLE `days`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `schedule`
--
ALTER TABLE `schedule`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fk_schedule_days_idx` (`day_id`),
  ADD KEY `fk_schedule_venues1_idx` (`venue_id`),
  ADD KEY `fk_schedule_teams1_idx` (`away_team_id`),
  ADD KEY `fk_schedule_teams2_idx` (`home_team_id`);

--
-- Indexes for table `teams`
--
ALTER TABLE `teams`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `venues`
--
ALTER TABLE `venues`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `days`
--
ALTER TABLE `days`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `schedule`
--
ALTER TABLE `schedule`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT for table `teams`
--
ALTER TABLE `teams`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `venues`
--
ALTER TABLE `venues`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `schedule`
--
ALTER TABLE `schedule`
  ADD CONSTRAINT `fk_schedule_days` FOREIGN KEY (`day_id`) REFERENCES `days` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_schedule_teams1` FOREIGN KEY (`away_team_id`) REFERENCES `teams` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_schedule_teams2` FOREIGN KEY (`home_team_id`) REFERENCES `teams` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_schedule_venues1` FOREIGN KEY (`venue_id`) REFERENCES `venues` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
