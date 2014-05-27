<?hh // strict
namespace Fastuc\Seo;

class SitemapUrl
{
	private string $location;
	private string $changeFrequency;
	private float $priority;

	public function __construct( $location, $changeFrequency, $priority )
	{
		$this->location = $location;
		$this->changeFrequency = $changeFrequency;
		$this->priority = $priority;
	}

	public function getLocation() : string
	{
		return $this->location;
	}

	public function getChangeFrequency() : string
	{
		return $this->changeFrequency;
	}

	public function getPriority() : float
	{
		return $this->priority;
	}
}

