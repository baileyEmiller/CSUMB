using UnityEngine;
using System.Collections;
using UnityEngine.AI;

[RequireComponent(typeof(Enemy))]
public class EnemyMovement : MonoBehaviour {

	private Transform target;

	private Enemy enemy;

	private NavMeshAgent navigation;

	void Start()
	{
		enemy = GetComponent<Enemy>();
		target = Waypoints.points[0];
		navigation = GetComponent<NavMeshAgent>();
		navigation.SetDestination(target.position);
	}


	void EndPath()
	{
		PlayerStats.Lives--;
		WaveSpawner.EnemiesAlive--;
		Destroy(gameObject);
	}

}
